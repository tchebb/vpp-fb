const unsigned short coeff_vred_2_5[33][12] = {
    {0x000f, 0x006f, 0x00f0, 0x012e, 0x00f0, 0x006f, 0x000f, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000e, 0x006d, 0x00ee, 0x012e, 0x00f2, 0x0071, 0x0010, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000d, 0x006b, 0x00ec, 0x012f, 0x00f3, 0x0073, 0x0011, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000d, 0x0069, 0x00eb, 0x012d, 0x00f5, 0x0075, 0x0012, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000c, 0x0067, 0x00e9, 0x012d, 0x00f7, 0x0077, 0x0013, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000b, 0x0065, 0x00e7, 0x012d, 0x00f9, 0x0079, 0x0014, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000a, 0x0063, 0x00e5, 0x012e, 0x00fa, 0x007b, 0x0015, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0009, 0x0061, 0x00e3, 0x012e, 0x00fc, 0x007d, 0x0016, 0x080a, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0009, 0x005f, 0x00e1, 0x012c, 0x00fe, 0x007f, 0x0017, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0008, 0x005d, 0x00df, 0x012d, 0x00ff, 0x0081, 0x0018, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0007, 0x005c, 0x00de, 0x012b, 0x0101, 0x0083, 0x0019, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0006, 0x005a, 0x00dc, 0x012c, 0x0102, 0x0085, 0x001a, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0006, 0x0058, 0x00da, 0x012b, 0x0103, 0x0087, 0x001c, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0005, 0x0056, 0x00d8, 0x012b, 0x0105, 0x0089, 0x001d, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0004, 0x0054, 0x00d6, 0x012b, 0x0107, 0x008b, 0x001e, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0004, 0x0052, 0x00d4, 0x012b, 0x0108, 0x008d, 0x001f, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0003, 0x0051, 0x00d2, 0x012a, 0x010a, 0x008f, 0x0020, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0002, 0x004f, 0x00d0, 0x012a, 0x010b, 0x0091, 0x0022, 0x0809, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0002, 0x004d, 0x00ce, 0x0128, 0x010c, 0x0094, 0x0023, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0001, 0x004b, 0x00cc, 0x0128, 0x010e, 0x0096, 0x0024, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0001, 0x004a, 0x00ca, 0x0127, 0x010f, 0x0098, 0x0025, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0048, 0x00c8, 0x0126, 0x0111, 0x009a, 0x0027, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0046, 0x00c6, 0x0126, 0x0112, 0x009c, 0x0028, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0801, 0x0045, 0x00c4, 0x0125, 0x0113, 0x009e, 0x0029, 0x0807, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0801, 0x0043, 0x00c2, 0x0124, 0x0114, 0x00a0, 0x002b, 0x0807, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0802, 0x0041, 0x00c0, 0x0124, 0x0116, 0x00a2, 0x002c, 0x0807, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0802, 0x0040, 0x00be, 0x0123, 0x0117, 0x00a4, 0x002d, 0x0807, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0803, 0x003e, 0x00bb, 0x0122, 0x0118, 0x00a7, 0x002f, 0x0806, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0803, 0x003c, 0x00b9, 0x0122, 0x0119, 0x00a9, 0x0030, 0x0806, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0804, 0x003b, 0x00b7, 0x0121, 0x011a, 0x00ab, 0x0032, 0x0806, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0804, 0x0039, 0x00b5, 0x0120, 0x011b, 0x00ad, 0x0033, 0x0805, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0804, 0x0038, 0x00b3, 0x011e, 0x011c, 0x00af, 0x0035, 0x0805, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0805, 0x0036, 0x00b1, 0x011e, 0x011e, 0x00b1, 0x0036, 0x0805, 0x0000, 0x0000, 0x0000, 0x0000},
};
