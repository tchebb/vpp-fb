const unsigned short coeff_hred_1_1[33][12] = {
    {0x080a, 0x080d, 0x0043, 0x088d, 0x00cf, 0x031a, 0x00cf, 0x088d, 0x0043, 0x080d, 0x080a, 0x000a},
    {0x0809, 0x080e, 0x0044, 0x088b, 0x00c3, 0x0318, 0x00dc, 0x088f, 0x0042, 0x080b, 0x080b, 0x000a},
    {0x0808, 0x0810, 0x0044, 0x0888, 0x00b6, 0x031a, 0x00e8, 0x0891, 0x0040, 0x080a, 0x080c, 0x000b},
    {0x0807, 0x0811, 0x0045, 0x0886, 0x00aa, 0x0318, 0x00f5, 0x0893, 0x003f, 0x0808, 0x080d, 0x000b},
    {0x0806, 0x0812, 0x0046, 0x0883, 0x009e, 0x0315, 0x0102, 0x0894, 0x003d, 0x0806, 0x080e, 0x000b},
    {0x0805, 0x0814, 0x0046, 0x0880, 0x0092, 0x0315, 0x010e, 0x0896, 0x003c, 0x0805, 0x080f, 0x000c},
    {0x0805, 0x0815, 0x0047, 0x087d, 0x0086, 0x0313, 0x011b, 0x0897, 0x003a, 0x0803, 0x0810, 0x000c},
    {0x0804, 0x0816, 0x0047, 0x087a, 0x007a, 0x0310, 0x0129, 0x0898, 0x0038, 0x0801, 0x0811, 0x000c},
    {0x0803, 0x0817, 0x0047, 0x0877, 0x006f, 0x030d, 0x0135, 0x0898, 0x0036, 0x0001, 0x0812, 0x000c},
    {0x0802, 0x0818, 0x0047, 0x0873, 0x0064, 0x0308, 0x0142, 0x0899, 0x0034, 0x0003, 0x0813, 0x000d},
    {0x0801, 0x0819, 0x0047, 0x0870, 0x0059, 0x0303, 0x014f, 0x0899, 0x0032, 0x0005, 0x0813, 0x000d},
    {0x0000, 0x081a, 0x0047, 0x086c, 0x004e, 0x02ff, 0x015b, 0x0899, 0x0030, 0x0007, 0x0814, 0x000d},
    {0x0001, 0x081b, 0x0047, 0x0868, 0x0043, 0x02fb, 0x0169, 0x0899, 0x002d, 0x0008, 0x0815, 0x000d},
    {0x0001, 0x081c, 0x0046, 0x0865, 0x0038, 0x02f7, 0x0177, 0x0898, 0x002b, 0x000a, 0x0816, 0x000d},
    {0x0002, 0x081d, 0x0046, 0x0861, 0x002e, 0x02f2, 0x0184, 0x0898, 0x0028, 0x000c, 0x0817, 0x000d},
    {0x0003, 0x081e, 0x0045, 0x085d, 0x0024, 0x02ec, 0x0190, 0x0897, 0x0026, 0x000e, 0x0818, 0x000e},
    {0x0004, 0x081e, 0x0045, 0x0859, 0x001a, 0x02e5, 0x019d, 0x0896, 0x0023, 0x0010, 0x0819, 0x000e},
    {0x0004, 0x081f, 0x0044, 0x0855, 0x0011, 0x02de, 0x01aa, 0x0894, 0x0020, 0x0012, 0x0819, 0x000e},
    {0x0005, 0x081f, 0x0043, 0x0851, 0x0008, 0x02d8, 0x01b6, 0x0893, 0x001d, 0x0014, 0x081a, 0x000e},
    {0x0006, 0x0820, 0x0042, 0x084d, 0x0802, 0x02d2, 0x01c3, 0x0891, 0x001a, 0x0016, 0x081b, 0x000e},
    {0x0006, 0x0820, 0x0041, 0x0849, 0x080a, 0x02cb, 0x01d0, 0x088f, 0x0016, 0x0018, 0x081c, 0x000e},
    {0x0007, 0x0821, 0x0040, 0x0844, 0x0813, 0x02c1, 0x01dc, 0x088c, 0x0013, 0x001b, 0x081c, 0x000e},
    {0x0007, 0x0821, 0x003f, 0x0840, 0x081b, 0x02ba, 0x01e8, 0x088a, 0x0010, 0x001d, 0x081d, 0x000e},
    {0x0008, 0x0821, 0x003e, 0x083c, 0x0823, 0x02b1, 0x01f4, 0x0887, 0x000c, 0x001f, 0x081d, 0x000e},
    {0x0009, 0x0822, 0x003c, 0x0838, 0x082b, 0x02a9, 0x0201, 0x0884, 0x0009, 0x0021, 0x081e, 0x000e},
    {0x0009, 0x0822, 0x003b, 0x0833, 0x0833, 0x02a1, 0x020d, 0x0880, 0x0005, 0x0023, 0x081f, 0x000d},
    {0x000a, 0x0822, 0x003a, 0x082f, 0x083a, 0x0297, 0x0218, 0x087c, 0x0001, 0x0025, 0x081f, 0x000d},
    {0x000a, 0x0822, 0x0038, 0x082b, 0x0841, 0x028f, 0x0224, 0x0878, 0x0802, 0x0026, 0x0820, 0x000d},
    {0x000a, 0x0822, 0x0036, 0x0827, 0x0848, 0x0286, 0x0230, 0x0874, 0x0806, 0x0028, 0x0820, 0x000d},
    {0x000b, 0x0822, 0x0035, 0x0823, 0x084e, 0x027b, 0x023b, 0x0870, 0x080a, 0x002a, 0x0820, 0x000d},
    {0x000b, 0x0822, 0x0033, 0x081e, 0x0855, 0x0272, 0x0247, 0x086b, 0x080e, 0x002c, 0x0821, 0x000c},
    {0x000c, 0x0821, 0x0032, 0x081a, 0x085b, 0x0266, 0x0251, 0x0866, 0x0812, 0x002e, 0x0821, 0x000c},
    {0x000c, 0x0821, 0x0030, 0x0816, 0x0860, 0x025b, 0x025b, 0x0860, 0x0816, 0x0030, 0x0821, 0x000c},
};