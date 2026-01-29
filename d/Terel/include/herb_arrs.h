/* 
 *
 * Categorized herb arrays to use with herbsearch.
 *
 * Goldberry, November 1999
 * Last updated - 11181999, by Goldberry
 *************************************************
 *
 * ANY_HERBS - herbs that can grow anywhere
 * FOREST_HERBS - herbs that thrive in forests or
 *   forest-like areas.
 * SWAMP_HERBS - herbs that thrive in swamps and
 *   marshes.
 * RIVER_HERBS - herbs that thrive on riverbanks or
 *   close to rivers.
 * PLAINS_HERBS - herbs that can grown in open plains
 *   or open fields type areas.
 * BEACH_HERBS - herbs that thrive on or near salt-water 
 *  beaches.
 * WARM_HERBS - herbs that thrive in warmer climates.
 * FROST_HERBS - herbs that thrive in snow-covered or
 *  frosty areas.
 * DARK_HERBS - herbs that thrive in areas with little
 *  or no light.
 * SUBT_HERBS - herbs that thrive in subterranean areas,
 *  usually with fresh-water sources nearby.
 * MOUNT_HERBS - herbs that thrive in higher-elevations,
 *  on mountain-sides or hill-tops. 
 * OCEAN_HERBS - herbs found in salt-water oceans.
 * WATER_HERBS - herbs found in fresh-water sources.
 * GARDEN_HERBS - garden variety herbs.
 * SPICE_HERBS - common spices (found in pantries, spice-
 *  gardens, spice-racks, etc.)
 * Guild-specific herb arrays for magic users:
 * MM_HERBS      - Herbs used by Morgul Mages
 * RANGER_HERBS  - Herbs used by Rangers
 *
 **************************************************
 */

#define MM_HERBS     ({ (GON_HERB + "angurth"),\
                        (GON_HERB + "coccinea"),\
                        (GON_HERB + "curugwath"),\
                        (GON_HERB + "frostheal"),\
                        (GON_HERB + "sumac"),\
                      })

#define RANGER_HERBS ({ (GON_HERB + "athelas"),\
                        (SHI_HERB + "pawnrose"),\
                      })
					  
#define ANY_HERBS    ({(GON_HERB + "angurth"),\
                       (GON_HERB + "astaldo"),\
                       (GON_HERB + "attanar"),\
                       (GON_HERB + "blueberry"),\
                       (GON_HERB + "blung"),\
                       (GON_HERB + "caraway"),\
                       (GON_HERB + "catnip"),\
                       (GON_HERB + "chervil"),\
                       (GON_HERB + "coccinea"),\
                       (GON_HERB + "fennel"),\
                       (GON_HERB + "foxglove"),\
                       (GON_HERB + "gonion"),\
                       (GON_HERB + "hemlock"),\
                       (GON_HERB + "holly"),\
                       (GON_HERB + "lothore"),\
                       (GON_HERB + "myrtle"),\
                       (GON_HERB + "redweed"),\
                       (GON_HERB + "rosemary"),\
                       (GON_HERB + "rpotato"),\
                       (GON_HERB + "seregon"),\
                       (GON_HERB + "sumac"),\
                       (GON_HERB + "suranie"),\
                       (GON_HERB + "tarragon"),\
                       (GON_HERB + "ungolestel"),\
                       (GON_HERB + "tuo"),\
                       (AVE_HERB + "mittikna"),\
                       (AVE_HERB + "carlith"),\
                       (SHI_HERB + "parsley"),\
                       (SHI_HERB + "pawnrose"),\
                       (SHI_HERB + "lianor_berry"),\
                     })

#define FOREST_HERBS ({(TER_HERB + "lukilvor"),\
                       (TER_HERB + "argil"),\
                       (TER_HERB + "sebre"),\
                       (KHA_HERB + "cedar_bark"),\
                       (KHA_HERB + "green_pine"),\
                       (KRY_HERB + "amanita"),\
                       (KRY_HERB + "bunchberry"),\
                       (KRY_HERB + "chantrelle"),\
                       (KRY_HERB + "cladina"),\
                       (KRY_HERB + "cranberry"),\
                       (KRY_HERB + "fdlhead"),\
                       (KRY_HERB + "hazelnut"),\
                       (KRY_HERB + "horsetail"),\
                       (KRY_HERB + "labr_tea"),\
                       (KRY_HERB + "lady_slipper"),\
                       (KRY_HERB + "onoclea"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "saskatoon"),\
                       (KRY_HERB + "sphagnum"),\
                       (KRY_HERB + "tiger_lily"),\
                       (KRY_HERB + "asparagus"),\
                       (KRY_HERB + "bkd_sedge"),\
                       (KRY_HERB + "blk_currant"),\
                       (KRY_HERB + "chicory"),\
                       (KRY_HERB + "chokecherry"),\
                       (KRY_HERB + "dandelion"),\
                       (KRY_HERB + "fireweed"),\
                       (KRY_HERB + "grey_willow"),\
                       (KRY_HERB + "hawthorn"),\
                       (KRY_HERB + "hop"),\
                       (KRY_HERB + "jewelweed"),\
                       (KRY_HERB + "raspberry"),\
                       (KRY_HERB + "sarsaparilla"),\
                       (KRY_HERB + "veronica"),\
                       (KRY_HERB + "wild_plum"),\
                       (GON_HERB + "suranie"),\
                       (GON_HERB + "mint"),\
                       (SHI_HERB + "parsley"),\
                       (SHI_HERB + "treemushroom"),\
                       (SHI_HERB + "pawnrose"),\
                       (SHI_HERB + "huckleberry"),\
                       (SHI_HERB + "lianor_berry"),\
                     })

#define SWAMP_HERBS  ({(KRY_HERB + "asparagus"),\
                       (KRY_HERB + "bkd_sedge"),\
                       (KRY_HERB + "bur_reed"),\
                       (KRY_HERB + "cattail"),\
                       (KRY_HERB + "cranberry"),\
                       (KRY_HERB + "grey_willow"),\
                       (KRY_HERB + "mandrake"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "raspberry"),\
                       (KRY_HERB + "sphagnum"),\
                       (KRY_HERB + "veronica"),\
                       (KRY_HERB + "wild_cuke"),\
                       (AVE_HERB + "strangleweed"),\
                       (GON_HERB + "curugwath"),\
                       (GON_HERB + "tyelka"),\
                     })

#define RIVER_HERBS  ({(KRY_HERB + "asparagus"),\
                       (KRY_HERB + "jewelweed"),\
                       (KRY_HERB + "bkd_sedge"),\
                       (KRY_HERB + "bur_reed"),\
                       (KRY_HERB + "chokecherry"),\
                       (KRY_HERB + "grey_willow"),\
                       (KRY_HERB + "hop"),\
                       (KRY_HERB + "horsetail"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "raspberry"),\
                       (KRY_HERB + "saskatoon"),\
                       (KRY_HERB + "wild_cuke"),\
                       (AVE_HERB + "strangleweed"),\
                       (GON_HERB + "curugwath"),\
                       (GON_HERB + "tyelka"),\
                       (SHI_HERB + "adillyp"),\
                     })

#define PLAINS_HERBS ({(KRY_HERB + "breadroot"),\
                       (KRY_HERB + "chicory"),\
                       (KRY_HERB + "cladina"),\
                       (KRY_HERB + "crocus"),\
                       (KRY_HERB + "dandelion"),\
                       (KRY_HERB + "fireweed"),\
                       (KRY_HERB + "grey_willow"),\
                       (KRY_HERB + "hawthorn"),\
                       (KRY_HERB + "horsetail"),\
                       (KRY_HERB + "locoweed"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "raspberry"),\
                       (KRY_HERB + "saskatoon"),\
                       (KRY_HERB + "sm_camas"),\
                       (KRY_HERB + "soapweed"),\
                       (KRY_HERB + "tiger_lily"),\
                     })

#define BEACH_HERBS  ({(KRY_HERB + "bch_plum"),\
                       (KRY_HERB + "bch_willow"),\
                       (KRY_HERB + "cattail"),\
                       (KRY_HERB + "cord_grass"),\
                       (KRY_HERB + "dandelion"),\
                       (KRY_HERB + "horsetail"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "salt_wort"),\
                       (KRY_HERB + "ss_grass"),\
                     })

#define WARM_HERBS   ({(KRY_HERB + "chicory"),\
                       (KRY_HERB + "locoweed"),\
                       (KRY_HERB + "poison_ivy"),\
                       (KRY_HERB + "raspberry"),\
                       (GON_HERB + "basil"),\
                       (GON_HERB + "dill"),\
                       (GON_HERB + "laurel"),\
                       (GON_HERB + "garlic"),\
                       (GON_HERB + "ginger"),\
                       (GON_HERB + "marjoram"),\
                       (GON_HERB + "oregano"),\
                       (GON_HERB + "red_pepper"),\
                       (GON_HERB + "rosemary"),\
                       (GON_HERB + "saffron"),\
                       (GON_HERB + "sage"),\
                       (GON_HERB + "savory"),\
                       (GON_HERB + "thyme"),\
                       (GON_HERB + "culkas"),\
                       (AVE_HERB + "belladonna"),\
                       (AVE_HERB + "nightshade"),\
                       (TER_HERB + "aravelis"),\
                       (SHI_HERB + "pawnrose"),\
                     })

#define FROST_HERBS  ({(GON_HERB + "frostheal"),\
                       (GON_HERB + "mint"),\
                       (GON_HERB + "madwort"),\
                       (TER_HERB + "sebre"),\
                       (TER_HERB + "argil"),\
                       (TER_HERB + "whitehorn"),\
                       (GON_HERB + "holly"),\
                       (GON_HERB + "blung"),\
                       (GON_HERB + "sumac"),\
                       (GON_HERB + "suranie"),\
                     })

#define DARK_HERBS   ({(GON_HERB + "curugwath"),\
                       (GON_HERB + "simbelmyne"),\
                       (GON_HERB + "tyelka"),\
                       (GON_HERB + "blung"),\
                       (AVE_HERB + "narcissus"),\
                       (AVE_HERB + "fordinfa"),\
                     })

#define SUBT_HERBS   ({(GON_HERB + "tyelka"),\
                       (GON_HERB + "curugwath"),\
                       (GON_HERB + "simbelmyne"),\
                       (GON_HERB + "tuo"),\
                       (AVE_HERB + "narcissus"),\
                       (AVE_HERB + "fordinfa"),\
                     })

#define MOUNT_HERBS  ({(TER_HERB + "ylpi"),\
                       (TER_HERB + "whitehorn"),\
                       (TER_HERB + "argil"),\
                       (TER_HERB + "sebre"),\
                       (TER_HERB + "lukilvor"),\
                       (GON_HERB + "sumac"),\
                       (GON_HERB + "suranie"),\
                       (GON_HERB + "madwort"),\
                       (SHI_HERB + "pawnrose"),\
                     })

#define OCEAN_HERBS  ({(KRY_HERB + "coral_alga"),\
                       (KRY_HERB + "cord_grass"),\
                       (KRY_HERB + "eel_grass"),\
                       (KRY_HERB + "fucus"),\
                       (KRY_HERB + "salt_wort"),\
                       (KRY_HERB + "sea_bubble"),\
                       (KRY_HERB + "sea_lettuce"),\
                       (KRY_HERB + "surf_grass"),\
                       (KRY_HERB + "bull_kelp"),\
                       (KRY_HERB + "elkhorn_kelp"),\
                       (KRY_HERB + "laminaria"),\
                       (KRY_HERB + "sargassum"),\
                       (AVE_HERB + "nethra"),\
                     })

#define WATER_HERBS  ({(AVE_HERB + "nethra"),\
                       (GON_HERB + "tyelka"),\
                       (TER_HERB + "moosho"),\
                       (SHI_HERB + "adillyp"),\
                     })

#define GARDEN_HERBS ({(GON_HERB + "blueberry"),\
                       (GON_HERB + "gonion"),\
                       (GON_HERB + "rosemary"),\
                       (GON_HERB + "rpotato"),\
                       (KRY_HERB + "asparagus"),\
                       (KRY_HERB + "raspberry"),\
                       (KRY_HERB + "wild_plum"),\
                       (GON_HERB + "mint"),\
                       (GON_HERB + "basil"),\
                       (GON_HERB + "dill"),\
                       (GON_HERB + "garlic"),\
                       (GON_HERB + "ginger"),\
                       (GON_HERB + "marjoram"),\
                       (GON_HERB + "oregano"),\
                       (GON_HERB + "red_pepper"),\
                       (GON_HERB + "saffron"),\
                       (GON_HERB + "sage"),\
                       (GON_HERB + "savory"),\
                       (GON_HERB + "thyme"),\
                       (GON_HERB + "strawberry"),\
                       (SHI_HERB + "parsley"),\
                     })

#define SPICE_HERBS  ({(GON_HERB + "rosemary"),\
                       (GON_HERB + "mint"),\
                       (GON_HERB + "basil"),\
                       (GON_HERB + "dill"),\
                       (GON_HERB + "garlic"),\
                       (GON_HERB + "ginger"),\
                       (GON_HERB + "marjoram"),\
                       (GON_HERB + "oregano"),\
                       (GON_HERB + "red_pepper"),\
                       (GON_HERB + "saffron"),\
                       (GON_HERB + "sage"),\
                       (GON_HERB + "savory"),\
                       (GON_HERB + "thyme"),\
                       (SHI_HERB + "parsley"),\
                     })



