#define GEM_TYPES	({ "quartz", "amber", "agate", "jasper", "onyx",  \
                           "garnet", "jade", "beryl", \
                           "opal", "topaz", "sapphire", \
                           "ruby", "emerald", "diamond", })
#define GEM_VALUES	({ 12, 72, 144,  216,  288,  432,  576,  864, \
                          1152, 1728, 2304, 3456, 4608, 6912, })
#define GEM_WEIGHT	({   6,    6,    6,    6,    6,    6,    6,    6, \
                             6,    6,    6,    6,    6,    6, })
#define GEM_VOLUME	({   8,   8,   6,    4,    3,    3,    2,    2, \
                             1,    1,    1,    1,    1,    1, })
// number of gems in the array that have a value too low for
// accepting them as spell ingredient.
#define GEMS_NOT_INGREDIENT	2
#define GEMS_FOR_SMITHS_BONUS  ({ "opal", "topaz", "sapphire", "ruby", \
                                  "emerald", "diamond", })
