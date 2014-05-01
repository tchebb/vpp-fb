/*******************************************************************************
* Copyright (C) Marvell International Ltd. and its affiliates
*
* Marvell GPL License Option
*
* If you received this File from Marvell, you may opt to use, redistribute and/or
* modify this File in accordance with the terms and conditions of the General
* Public License Version 2, June 1991 (the "GPL License"), a copy of which is
* available along with the File in the license.txt file or by writing to the Free
* Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
* on the worldwide web at http://www.gnu.org/licenses/gpl.txt.
*
* THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
* WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
* DISCLAIMED.  The GPL License provides additional details about this warranty
* disclaimer.
********************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h> // for msleep()
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/videodev2.h>
#include <asm/cacheflush.h> // for __cpuc_flush_dcache_area(fbBuf, length);
#include <asm/outercache.h>
#include <asm/page.h>
#include <asm/io.h>
#include <mach/irqs.h>

#include "galois_io.h"
#include "thinvpp_api.h"
#include "thinvpp_isr.h"
#include "api_dhub.h"
#include "api_avio_dhub.h"
#include "memmap.h"

#include "avpll.h"

// TODO: Proper return values

/*******************************************************************************
  Module API defined
  */

#define bTST(x, b) (((x) >> (b)) & 1)

#define VPPFB_DEVICE_TAG                       "[Galois][fbdev_driver] "

void VPP_dhub_sem_clear(void);

/*******************************************************************************
  Macro Defined
  */

#ifdef ENABLE_DEBUG
#define gs_debug(...)   printk(KERN_DEBUG VPPFB_DEVICE_TAG __VA_ARGS__)
#else
#define gs_debug(...)
#endif

#define gs_info(...)    printk(KERN_INFO VPPFB_DEVICE_TAG __VA_ARGS__)
#define gs_notice(...)  printk(KERN_NOTICE VPPFB_DEVICE_TAG __VA_ARGS__)

#define gs_trace(...)   printk(KERN_WARNING VPPFB_DEVICE_TAG __VA_ARGS__)
#define gs_error(...)   printk(KERN_ERR VPPFB_DEVICE_TAG __VA_ARGS__)

/*******************************************************************************
  Module Variable
  */

struct vpp_fb_par {
	fb_device_t vppfb_ctx;

	u64 last_isr_time;
	unsigned last_isr_interval;
	volatile int fb_isr_count;
};

static struct fb_fix_screeninfo vpp_fb_fix __devinitdata = {
	.id           = "VPP FB",
	.capabilities = FB_CAP_FOURCC,
	.type         = FB_TYPE_PACKED_PIXELS,
	.visual       = FB_VISUAL_TRUECOLOR,
	.xpanstep     = 1,
	.ypanstep     = 1,
	.ywrapstep    = 1,
	.accel        = FB_ACCEL_NONE,
};

static struct fb_var_screeninfo vpp_fb_var __devinitdata = {
	.xres = 1280,
	.yres = 720,
	.xres_virtual = 1280,
	.yres_virtual = 720,
	.bits_per_pixel = 16,
	.grayscale = V4L2_PIX_FMT_YUYV,
};

static irqreturn_t vppfb_devices_vpp_isr(int irq, void *dev_id)
{
	struct fb_info *info = dev_id;
	struct vpp_fb_par *par = info->par;

	int instat;
	HDL_semaphore *pSemHandle;
	u64 cpcb0_isr_time_current;

	++par->vppfb_ctx.count;
	par->fb_isr_count++;

	cpcb0_isr_time_current = cpu_clock(smp_processor_id());
	par->last_isr_interval = (unsigned) (cpcb0_isr_time_current - par->last_isr_time);
	par->last_isr_time = cpcb0_isr_time_current;

	/* VPP interrupt handling  */
	pSemHandle = dhub_semaphore(&VPP_dhubHandle.dhub);
	instat = semaphore_chk_full(pSemHandle, -1);

	if (bTST(instat, avioDhubSemMap_vpp_vppCPCB0_intr)) {
		/* our CPCB interrupt */
		/* clear interrupt */
		semaphore_pop(pSemHandle, avioDhubSemMap_vpp_vppCPCB0_intr, 1);
		semaphore_clr_full(pSemHandle, avioDhubSemMap_vpp_vppCPCB0_intr);

		if(par->fb_isr_count > 1)
		{
			THINVPP_CPCB_ISR_service(thinvpp_obj, CPCB_1);
		}
	}

	return IRQ_HANDLED;
}

static void vppfb_device_exit(struct fb_info *info)
{
	struct vpp_fb_par *par = info->par;

	MV_THINVPP_CloseDispWindow();
	MV_THINVPP_Stop();

	msleep(100); //100 milliseconds
	MV_THINVPP_Destroy();

	// FIX ME! Wrong pointer for free!
	if (par->vppfb_ctx.fbBuf) {
		dma_unmap_single(NULL, (dma_addr_t)par->vppfb_ctx.mapaddr, par->vppfb_ctx.length, DMA_TO_DEVICE);
		gs_trace("will free pBuf OK\n");
		kfree(par->vppfb_ctx.fbBuf);
		par->vppfb_ctx.fbBuf = NULL;
	}

	/* unregister VPP interrupt */
	msleep(100); //100 milliseconds
	free_irq(IRQ_DHUBINTRAVIO0, NULL);

	gs_trace("dev exit done\n");
}

static int vpp_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	*var = info->var;
	return 0;
}

// TODO: Can this be run while the hw is already initalized?
static int vpp_fb_set_par(struct fb_info *info)
{
	struct vpp_fb_par *par = info->par;
	int err = -ENOMEM;
	int vres;
	unsigned alloc_length;
	void* unalig_buf;

	// TODO: Fix this also (fb_screeninfo_var?)
	static VBUF_INFO vbuf;

	gs_info("drv init\n");

	// TODO: Is this needed?
	vres = MV_THINVPP_IsCPCBActive(CPCB_1);

	if (!vres)
	{
		gs_trace("vpp_fb is not enabled in bootloader\n");
		return -EINVAL; // do nothing if vppfb is not enabled in bootloader
	}
	if (vres != 524)
	{
		gs_trace("vpp_fb does not supprt vres=%d\n", vres);
		return -EINVAL; // do nothing if vres is not supported
	}

	if (info->var.xres != 1280 || info->var.yres != 720){
		gs_trace("vpp_fb does not support xres=%d, yres=%d\n",
			info->var.xres,
			info->var.yres);
		return -EINVAL;
	}

	/* create PE device */

	/* set up fb frame */
	vbuf.alpha   = 255;
	vbuf.bgcolor = 0x00800080;
	vbuf.m_disp_offset   = 0;
	vbuf.m_active_left   = 0; // TODO: Panning support?
	vbuf.m_active_top    = 0;
	vbuf.m_active_width  = info->var.xres;
	vbuf.m_active_height = info->var.yres;
	vbuf.m_buf_stride    = (info->var.bits_per_pixel / 8) * vbuf.m_active_width;

	info->fix.line_length = vbuf.m_buf_stride;

	par->vppfb_ctx.length = vbuf.m_buf_stride * vbuf.m_active_height;
	alloc_length = par->vppfb_ctx.length + PAGE_SIZE;
	unalig_buf = kmalloc(alloc_length, GFP_KERNEL | GFP_DMA);
	par->vppfb_ctx.fbBuf = (void*)ALIGN((uintptr_t)unalig_buf, PAGE_SIZE);

	printk("vppfb_ctx.fbBuf: %p\n", par->vppfb_ctx.fbBuf);
	if (!par->vppfb_ctx.fbBuf) {
		gs_trace("kmalloc error\n");
		return err;
	}

	par->vppfb_ctx.mapaddr = (unsigned int *)dma_map_single(NULL, par->vppfb_ctx.fbBuf, par->vppfb_ctx.length, DMA_TO_DEVICE);
	err = dma_mapping_error(NULL, (dma_addr_t)par->vppfb_ctx.fbBuf);
	printk("vppfb_ctx.mapaddr: %p\n", par->vppfb_ctx.mapaddr);
	if (err) {
		gs_trace("dma_mapping_error\n");
		/* FIX ME, wrong pointer! */
		kfree(par->vppfb_ctx.fbBuf);
		par->vppfb_ctx.fbBuf = NULL;
		return err;
	}

	outer_cache.flush_range(virt_to_phys(par->vppfb_ctx.fbBuf), virt_to_phys(par->vppfb_ctx.fbBuf)+par->vppfb_ctx.length);
	vbuf.m_pbuf_start = (void*)virt_to_phys(par->vppfb_ctx.fbBuf);

	// initialize buffer
	// TODO: YUV/RGB?
	memset(par->vppfb_ctx.fbBuf, 0, par->vppfb_ctx.length);
	info->screen_base = (char *)par->vppfb_ctx.fbBuf;
	info->fix.smem_start = (unsigned int)par->vppfb_ctx.mapaddr;
	info->fix.smem_len = par->vppfb_ctx.length;

	/* initialize dhub */
	DhubInitialization(CPUINDEX, VPP_DHUB_BASE, VPP_HBO_SRAM_BASE, &VPP_dhubHandle, VPP_config, VPP_NUM_OF_CHANNELS);
	DhubInitialization(CPUINDEX, AG_DHUB_BASE, AG_HBO_SRAM_BASE, &AG_dhubHandle, AG_config, AG_NUM_OF_CHANNELS);

	MV_THINVPP_Create(MEMMAP_VPP_REG_BASE, &par->vppfb_ctx);
	MV_THINVPP_Reset();
	MV_THINVPP_Config();
	AVPLL_Enable();

	/* set output resolution */
	MV_THINVPP_SetCPCBOutputResolution(CPCB_1, RES_720P5994, OUTPUT_BIT_DEPTH_8BIT);

	// use MAIN plane
	par->vppfb_ctx.planes = 1;
	par->vppfb_ctx.win.x = 0;
	par->vppfb_ctx.win.y = 0;
	par->vppfb_ctx.win.width = info->var.xres;
	par->vppfb_ctx.win.height = info->var.yres;
	MV_THINVPP_SetMainDisplayFrame(&vbuf);
	MV_THINVPP_OpenDispWindow(PLANE_MAIN, &par->vppfb_ctx.win, NULL);

	/* register ISR */
	err = request_irq(IRQ_DHUBINTRAVIO0, vppfb_devices_vpp_isr, IRQF_DISABLED, "vppfb_module_vpp", info);
	if (unlikely(err < 0)) {
		gs_trace("vec_num:%5d, err:%8x\n", IRQ_DHUBINTRAVIO0, err);
		return err;
	}

	/* clean up and enable ISR */
	VPP_dhub_sem_clear();
	semaphore_pop(thinvpp_obj->pSemHandle, avioDhubSemMap_vpp_vppCPCB0_intr, 1);
	semaphore_clr_full(thinvpp_obj->pSemHandle, avioDhubSemMap_vpp_vppCPCB0_intr);
	THINVPP_Enable_ISR_Interrupt(thinvpp_obj, CPCB_1, 1);

	return 0;
}

static struct fb_ops vpp_fb_ops = {
	.owner        = THIS_MODULE,
	.fb_check_var = vpp_fb_check_var,
	.fb_set_par   = vpp_fb_set_par,
	.fb_fillrect  = cfb_fillrect,
	.fb_copyarea  = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
};

static int __init vpp_fb_probe (struct platform_device *pdev)
{
	struct fb_info *info;
	struct vpp_fb_par *par;
	struct device *device = &pdev->dev;

	/*
	 * Dynamically allocate info and par
	 */
	info = framebuffer_alloc(sizeof(struct vpp_fb_par), device);

	if (!info) {
		/* goto error path */
	}

	par = info->par;

	/* 
	 * Here we set the screen_base to the virtual memory address
	 * for the framebuffer. Usually we obtain the resource address
	 * from the bus layer and then translate it to virtual memory
	 * space via ioremap. Consult ioport.h. 
	 */
	//info->screen_base = framebuffer_virtual_memory;
	info->fbops = &vpp_fb_ops;
	info->fix = vpp_fb_fix; /* this will be the only time vpp_fb_fix will be
				* used, so mark it as __devinitdata
				*/
#if 0
	info->pseudo_palette = pseudo_palette; /* The pseudopalette is an
						* 16-member array
						*/
#endif
	/*
	 * Set up flags to indicate what sort of acceleration your
	 * driver can provide (pan/wrap/copyarea/etc.) and whether it
	 * is a module -- see FBINFO_* in include/linux/fb.h
	 *
	 * If your hardware can support any of the hardware accelerated functions
	 * fbcon performance will improve if info->flags is set properly.
	 *
	 * FBINFO_HWACCEL_COPYAREA - hardware moves
	 * FBINFO_HWACCEL_FILLRECT - hardware fills
	 * FBINFO_HWACCEL_IMAGEBLIT - hardware mono->color expansion
	 * FBINFO_HWACCEL_YPAN - hardware can pan display in y-axis
	 * FBINFO_HWACCEL_YWRAP - hardware can wrap display in y-axis
	 * FBINFO_HWACCEL_DISABLED - supports hardware accels, but disabled
	 * FBINFO_READS_FAST - if set, prefer moves over mono->color expansion
	 * FBINFO_MISC_TILEBLITTING - hardware can do tile blits
	 *
	 * NOTE: These are for fbcon use only.
	 */
	info->flags = FBINFO_DEFAULT;

	// TODO: Figure this out
#if 0
	/*
	 * This should give a reasonable default video mode. The following is
	 * done when we can set a video mode. 
	 */
	if (!mode_option)
	mode_option = "640x480@60";	 	

	retval = fb_find_mode(&info->var, info, mode_option, NULL, 0, NULL, 8);

	if (!retval || retval == 4)
	return -EINVAL;			

	/* This has to be done! */
	if (fb_alloc_cmap(&info->cmap, cmap_len, 0))
		return -ENOMEM;
#endif

	/* 
	 * The following is done in the case of having hardware with a static 
	 * mode. If we are setting the mode ourselves we don't call this. 
	 */	
	info->var = vpp_fb_var;

	/*
	 * For drivers that can...
	 */
	//xxxfb_check_var(&info->var, info);

	/*
	 * Does a call to fb_set_par() before register_framebuffer needed?  This
	 * will depend on you and the hardware.  If you are sure that your driver
	 * is the only device in the system, a call to fb_set_par() is safe.
	 *
	 * Hardware in x86 systems has a VGA core.  Calling set_par() at this
	 * point will corrupt the VGA console, so it might be safer to skip a
	 * call to set_par here and just allow fbcon to do it for you.
	 */
	vpp_fb_set_par(info);

	if (register_framebuffer(info) < 0) {
	fb_dealloc_cmap(&info->cmap);
	return -EINVAL;
	}
	printk(KERN_INFO "fb%d: %s frame buffer device\n", info->node,
	   info->fix.id);
	platform_set_drvdata(pdev, info);
	return 0;
}

static int __devexit vpp_fb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);

	if (info) {
		unregister_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		if (MV_THINVPP_IsCPCBActive(CPCB_1))
			vppfb_device_exit(info);

		gs_trace("drv exit done\n");

		framebuffer_release(info);
	}
	return 0;
}

static struct platform_driver vpp_fb_driver = {
	.probe     = vpp_fb_probe,
	.remove    = vpp_fb_remove,
	.driver = {
		.name  = "vpp_fb",
		.owner = THIS_MODULE,
	},
};

static struct platform_device *vpp_fb_device;

static int __init vpp_fb_init(void)
{
	int ret;

	ret = platform_driver_register(&vpp_fb_driver);

	if (!ret) {
		vpp_fb_device = platform_device_register_simple("vpp_fb", 0,
								NULL, 0);

		if (IS_ERR(vpp_fb_device)) {
			platform_driver_unregister(&vpp_fb_driver);
			ret = PTR_ERR(vpp_fb_device);
		}
	}

	return ret;
}

static void __exit vpp_fb_exit(void)
{
	platform_device_unregister(vpp_fb_device);
	platform_driver_unregister(&vpp_fb_driver);
}

module_init(vpp_fb_init);
module_exit(vpp_fb_exit);

MODULE_AUTHOR("Thomas Hebb <tommyhebb@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VPP framebuffer for Marvell 88DE3100");
