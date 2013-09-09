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
#include <asm/cacheflush.h> // for __cpuc_flush_dcache_area(logoBuf, length);
#include <asm/outercache.h>
#include <asm/page.h>
#include <asm/io.h>

#include "galois_io.h"
#include "thinvpp_api.h"
#include "thinvpp_isr.h"
#include "api_dhub.h"
#include "api_avio_dhub.h"
#include "Galois_memmap.h"
#include "bcm_cmds.h"

#if LOGO_USE_SHM
#include "shm_api.h"
#include "shm_type.h"
extern shm_device_t *shm_api_device_noncache;
#endif

// TODO: Proper return values

/*******************************************************************************
  Module API defined
  */

#define bTST(x, b) (((x) >> (b)) & 1)

#define FASTLOGO_DEVICE_TAG                       "[Galois][fbdev_driver] "

void VPP_dhub_sem_clear(void);

/*******************************************************************************
  Macro Defined
  */

#ifdef ENABLE_DEBUG
#define gs_debug(...)   printk(KERN_DEBUG FASTLOGO_DEVICE_TAG __VA_ARGS__)
#else
#define gs_debug(...)
#endif

#define gs_info(...)    printk(KERN_INFO FASTLOGO_DEVICE_TAG __VA_ARGS__)
#define gs_notice(...)  printk(KERN_NOTICE FASTLOGO_DEVICE_TAG __VA_ARGS__)

#define gs_trace(...)   printk(KERN_WARNING FASTLOGO_DEVICE_TAG __VA_ARGS__)
#define gs_error(...)   printk(KERN_ERR FASTLOGO_DEVICE_TAG __VA_ARGS__)

/*******************************************************************************
  Module Variable
  */

struct vpp_fb_par {
	logo_device_t fastlogo_ctx;

	u64 last_isr_time;
	unsigned last_isr_interval;
	volatile int logo_isr_count;
	volatile int cpcb_start_flag;
};

static struct fb_fix_screeninfo vpp_fb_fix __devinitdata = {
	.id        = "VPP FB", 
	.type      = FB_TYPE_PACKED_PIXELS,
	.visual    = FB_VISUAL_TRUECOLOR,
	.xpanstep  = 1,
	.ypanstep  = 1,
	.ywrapstep = 1, 
	.accel     = FB_ACCEL_NONE,
};

static struct fb_var_screeninfo vpp_fb_var __devinitdata = {
	.xres = 720,
	.yres = 480,
	.xres_virtual = 720,
	.yres_virtual = 480,
	.bits_per_pixel = 16,
	.red = {
		.offset = 0,
		.length = 4,
	},
	.green = {
		.offset = 4,
		.length = 4,
	},
	.blue = {
		.offset = 8,
		.length = 4,
	},
	.transp = {
		.offset = 12,
		.length = 4,
	},
};

static irqreturn_t fastlogo_devices_vpp_isr(int irq, void *dev_id)
{
	struct fb_info *info = dev_id;
	struct vpp_fb_par *par = info->par;

	int instat;
	HDL_semaphore *pSemHandle;
	u64 cpcb0_isr_time_current;

	++par->fastlogo_ctx.count;
	par->logo_isr_count++;

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

		if(par->logo_isr_count > 1)
		{
			THINVPP_CPCB_ISR_service(thinvpp_obj, CPCB_1, &par->cpcb_start_flag);
		}
	}

	return IRQ_HANDLED;
}

static void fastlogo_device_exit(struct fb_info *info)
{
	struct vpp_fb_par *par = info->par;

	MV_THINVPP_CloseDispWindow();
	MV_THINVPP_Stop();

	msleep(100); //100 milliseconds
	MV_THINVPP_Destroy();
#if LOGO_USE_SHM
	if (par->fastlogo_ctx.mSHMOffset != ERROR_SHM_MALLOC_FAILED)
	{
		MV_SHM_NONCACHE_Free(par->fastlogo_ctx.mSHMOffset);
		par->fastlogo_ctx.logoBuf = NULL;
		par->fastlogo_ctx.mSHMOffset = ERROR_SHM_MALLOC_FAILED;
	}
#else
	if (par->fastlogo_ctx.logoBuf) {
		dma_unmap_single(NULL, (dma_addr_t)par->fastlogo_ctx.mapaddr, par->fastlogo_ctx.length, DMA_TO_DEVICE);
		gs_trace("will free pBuf OK\n");
		kfree(par->fastlogo_ctx.logoBuf);
		par->fastlogo_ctx.logoBuf = NULL;
	}
#endif

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
	int err;
	int vres;

	// TODO: Fix this also (fb_screeninfo_var?)
	static VBUF_INFO vbuf;

	gs_info("drv init\n");

	// TODO: Is this needed?
	vres = MV_THINVPP_IsCPCBActive(CPCB_1);

	if (!vres)
	{
		gs_trace("vpp_fb is not enabled in bootloader\n");
		return -EINVAL; // do nothing if fastlogo is not enabled in bootloader
	}
	if (vres != 524)
	{
		gs_trace("vpp_fb does not supprt vres=%d\n", vres);
		return -EINVAL; // do nothing if vres is not supported
	}

	/* create PE device */

	/* set up logo frame */
	vbuf.alpha   = 255;
	vbuf.bgcolor = 0x00800080;
	vbuf.m_disp_offset   = 0;
	vbuf.m_active_left   = 0; // TODO: Panning support?
	vbuf.m_active_top    = 0;
	vbuf.m_active_width  = info->var.xres;
	vbuf.m_active_height = info->var.yres;
	vbuf.m_buf_stride    = (info->var.bits_per_pixel / 8) * vbuf.m_active_width;

	info->fix.line_length = vbuf.m_buf_stride;

	par->fastlogo_ctx.length = vbuf.m_buf_stride * vbuf.m_active_height;

#if LOGO_USE_SHM
	// use MV_SHM for logo buffer and 3 dhub queues to have contiguous memory
	par->fastlogo_ctx.mSHMSize = par->fastlogo_ctx.length +
		par->fastlogo_ctx.bcmQ_len + par->fastlogo_ctx.dmaQ_len + par->fastlogo_ctx.cfgQ_len;

	par->fastlogo_ctx.mSHMOffset = MV_SHM_NONCACHE_Malloc(par->fastlogo_ctx.mSHMSize, 4096);
	if (par->fastlogo_ctx.mSHMOffset == ERROR_SHM_MALLOC_FAILED)
	{
		return -1;
	}

	par->fastlogo_ctx.logoBuf = (int *) MV_SHM_GetNonCacheVirtAddr(par->fastlogo_ctx.mSHMOffset);
	par->fastlogo_ctx.mapaddr = (unsigned int *) MV_SHM_GetNonCachePhysAddr(par->fastlogo_ctx.mSHMOffset);

	// arrange dhub queues and commands
	{
		char *shm = (char *) par->fastlogo_ctx.logoBuf;
		unsigned shm_phys = (unsigned) par->fastlogo_ctx.mapaddr;
		par->fastlogo_ctx.bcmQ_len = bcmQ_len;
		par->fastlogo_ctx.dmaQ_len = 8*8;
		par->fastlogo_ctx.cfgQ_len = 8*8;
		par->fastlogo_ctx.bcmQ = shm + par->fastlogo_ctx.length;
		par->fastlogo_ctx.dmaQ = par->fastlogo_ctx.bcmQ + par->fastlogo_ctx.bcmQ_len;
		par->fastlogo_ctx.cfgQ = par->fastlogo_ctx.dmaQ + par->fastlogo_ctx.dmaQ_len;
		par->fastlogo_ctx.bcmQ_phys = shm_phys + par->fastlogo_ctx.length;
		par->fastlogo_ctx.dmaQ_phys = par->fastlogo_ctx.bcmQ_phys + par->fastlogo_ctx.bcmQ_len;
		par->fastlogo_ctx.cfgQ_phys = par->fastlogo_ctx.dmaQ_phys + par->fastlogo_ctx.dmaQ_len;

		// pre-load vpp commands
		memcpy(par->fastlogo_ctx.bcmQ, bcm_cmd_0, bcm_cmd_0_len);

		// pre-load logo frame dma commands
		logo_frame_dma_cmd[2] = shm_phys;
		vbuf.m_pbuf_start = (void *) shm_phys;
		memcpy(par->fastlogo_ctx.dmaQ, logo_frame_dma_cmd, logo_dma_cmd_len);
	}
#else
	par->fastlogo_ctx.logoBuf = kmalloc(par->fastlogo_ctx.length, GFP_KERNEL);
	if (!par->fastlogo_ctx.logoBuf) {
		gs_trace("kmalloc error\n");
		return err;
	}

	par->fastlogo_ctx.mapaddr = (unsigned int *)dma_map_single(NULL, par->fastlogo_ctx.logoBuf, par->fastlogo_ctx.length, DMA_TO_DEVICE);
	err = dma_mapping_error(NULL, (dma_addr_t)par->fastlogo_ctx.logoBuf);
	if (err) {
		gs_trace("dma_mapping_error\n");
		kfree(par->fastlogo_ctx.logoBuf);
		par->fastlogo_ctx.logoBuf = NULL;
		return err;
	}
	outer_cache.flush_range(virt_to_phys(par->fastlogo_ctx.logoBuf), virt_to_phys(par->fastlogo_ctx.logoBuf)+par->fastlogo_ctx.length);
	logo_frame_dma_cmd[2] = virt_to_phys(par->fastlogo_ctx.logoBuf);
	vbuf.m_pbuf_start = (void *) logo_frame_dma_cmd[2];
#endif

	// initialize buffer
	// TODO: YUV/RGB?
	memset(par->fastlogo_ctx.logoBuf, 0, par->fastlogo_ctx.length);
	info->screen_base = (char *)par->fastlogo_ctx.logoBuf;
	info->fix.smem_start = (unsigned int)par->fastlogo_ctx.mapaddr;
	info->fix.smem_len = par->fastlogo_ctx.length;

	/* initialize dhub */
	DhubInitialization(CPUINDEX, VPP_DHUB_BASE, VPP_HBO_SRAM_BASE, &VPP_dhubHandle, VPP_config, VPP_NUM_OF_CHANNELS);
	DhubInitialization(CPUINDEX, AG_DHUB_BASE, AG_HBO_SRAM_BASE, &AG_dhubHandle, AG_config, AG_NUM_OF_CHANNELS);

	MV_THINVPP_Create(MEMMAP_VPP_REG_BASE, &par->fastlogo_ctx);
	MV_THINVPP_Reset();
	MV_THINVPP_Config();

	/* set output resolution */
	MV_THINVPP_SetCPCBOutputResolution(CPCB_1, RES_525P5994, OUTPUT_BIT_DEPTH_8BIT);

	// use MAIN plane
	par->fastlogo_ctx.planes = 1;
	par->fastlogo_ctx.win.x = 0;
	par->fastlogo_ctx.win.y = 0;
	par->fastlogo_ctx.win.width = 720;
	par->fastlogo_ctx.win.height = 480;
	MV_THINVPP_SetMainDisplayFrame(&vbuf);
	MV_THINVPP_OpenDispWindow(PLANE_MAIN, &par->fastlogo_ctx.win, NULL);

	/* register ISR */
	err = request_irq(IRQ_DHUBINTRAVIO0, fastlogo_devices_vpp_isr, IRQF_DISABLED, "fastlogo_module_vpp", info);
	if (unlikely(err < 0)) {
		gs_trace("vec_num:%5d, err:%8x\n", IRQ_DHUBINTRAVIO0, err);
		return err;
	}

	/*
	 * using 3 for debugging legacy; should change to a more reasonable
	 * number after clean-up
	 */
	par->cpcb_start_flag = 3;

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
	int cmap_len, retval;	

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
			fastlogo_device_exit(info);

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
