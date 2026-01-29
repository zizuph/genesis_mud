//         /d/Avenir/common/herbs/herb_list.h
//
//         modified by Lilith for Avenir 
//         Dec 1996
/*
 *      /d/Gondor/common/lib/herb_list.h
 *
 *	Do not include this file!
 *	Do this instead:
 *	string *herbs = HERB_MASTER->query_herbs();
 *
 *	Then use 'herbs' as you would use HERBS when including this file!
 *
 *	Olorin, November 1995
 *
 * Revisions:
 * 	Lucius, Jul 2017: Moved the aliases and area herb lists
 * 	                  to here. It was sub-optimal to generate
 * 	                  them dynamically each time we queried.
 *  Lilith, Dec 2021: Fixed typo in alias list, updated herb list.
 */
#include "/d/Avenir/include/paths.h"
#define KALADHB "/d/Kalad/common/herbs/"

#define HERBS ({ AVHERB + "carlith", \
                 AVHERB + "fordinfa", \
                 AVHERB + "mittikna", \
                 AVHERB + "narcissus", \
                 AVHERB + "nethra", \
                 AVHERB + "nightshade", \
                 AVHERB + "strangleweed", \
                 GOHERB + "alfirin", \
                 GOHERB + "astaldo", \
                 GOHERB + "athelas", \
                 GOHERB + "attanar", \
                 GOHERB + "basil", \
                 GOHERB + "blueberry", \
                 GOHERB + "blung", \
                 GOHERB + "bpotato", \
                 GOHERB + "caraway", \
                 GOHERB + "catnip", \
                 GOHERB + "chervil", \
                 GOHERB + "clove", \
                 GOHERB + "coccinea", \
                 GOHERB + "curugwath", \
                 GOHERB + "dill", \
                 GOHERB + "fennel", \
                 GOHERB + "foxglove", \
                 GOHERB + "garlic", \
                 GOHERB + "ginger", \
                 GOHERB + "gonion", \
                 GOHERB + "handasse", \
                 GOHERB + "hemlock", \
                 GOHERB + "holly", \
                 GOHERB + "laurel", \
                 GOHERB + "lissuin", \
                 GOHERB + "lothore", \
                 GOHERB + "marjoram", \
                 GOHERB + "mint", \
                 GOHERB + "myrtle", \
                 GOHERB + "oregano", \
                 GOHERB + "redweed", \
                 GOHERB + "rosemary", \
                 GOHERB + "rpotato", \
                 GOHERB + "saffron", \
                 GOHERB + "sage", \
                 GOHERB + "savory", \
                 GOHERB + "seregon", \
                 GOHERB + "sumac", \
                 GOHERB + "suranie", \
                 GOHERB + "tarragon", \
                 GOHERB + "thyme", \
                 GOHERB + "tuo", \
                 GOHERB + "tyelka", \
                 GOHERB + "ungolestel", \
                 SHHERB + "parsley", \
                 SHHERB + "pawnrose", \
                 SHHERB + "huckleberry", \
                 SHHERB + "lianor_berry", \
                 SHHERB + "treemushroom", \
                 SHHERB + "adillyp", \
		 SHHERB + "bilberry",      \
                 SHHERB + "pindan",     \
		 KALADHB + "fungari", \
                 KALADHB + "blade", \
                 KRHERB + "amanita", \
                 KRHERB + "angeltear", \
                 KRHERB + "asparagus", \
                 KRHERB + "bch_plum", \
                 KRHERB + "bch_willow", \
                 KRHERB + "bkd_sedge", \
                 KRHERB + "blk_currant", \
                 KRHERB + "breadroot", \
                 KRHERB + "brownslime", \
                 KRHERB + "bull_kelp", \
                 KRHERB + "bunchberry", \
                 KRHERB + "bur_reed", \
                 KRHERB + "cattail", \
                 KRHERB + "chantrelle", \
                 KRHERB + "cladina", \
                 KRHERB + "coral_alga", \
                 KRHERB + "cord_grass", \
                 KRHERB + "cranberry", \
                 KRHERB + "crocus", \
                 KRHERB + "dandelion", \
                 KRHERB + "eel_grass", \
                 KRHERB + "elidross", \
                 KRHERB + "elkhorn_kelp", \
                 KRHERB + "fdlhead", \
                 KRHERB + "fireweed", \
                 KRHERB + "fucus", \
                 KRHERB + "greenslime", \
                 KRHERB + "grey_willow", \
                 KRHERB + "hawthorn", \
                 KRHERB + "hazelnut", \
                 KRHERB + "hop", \
                 KRHERB + "horsetail", \
                 KRHERB + "jewelweed", \
                 KRHERB + "labr_tea", \
                 KRHERB + "lady_slipper", \
                 KRHERB + "laminaria", \
                 KRHERB + "licorice", \
                 KRHERB + "locoweed", \
                 KRHERB + "mandrake", \
                 KRHERB + "onoclea", \
                 KRHERB + "poison_ivy", \
                 KRHERB + "raspberry", \
                 KRHERB + "salt_wort", \
                 KRHERB + "sargassum", \
                 KRHERB + "sarsaparilla", \
                 KRHERB + "saskatoon", \
                 KRHERB + "sea_bubble", \
                 KRHERB + "sea_lettuce", \
                 KRHERB + "skullcap", \
                 KRHERB + "sm_camas", \
                 KRHERB + "soapweed", \
                 KRHERB + "solinaith", \
                 KRHERB + "sphagnum", \
                 KRHERB + "ss_grass", \
                 KRHERB + "surf_grass", \
                 KRHERB + "tangleshoot", \
                 KRHERB + "tiger_lily", \
                 KRHERB + "veronica", \
                 KRHERB + "wild_cuke", \
                 KRHERB + "wild_plum", \
		 SHHERB + "bilberry",      \
                 SHHERB + "pindan", \
})

#define HERB_AREAS ([ \
    "arctic" : ({ GOHERB + "frostheal",		\
	          KRHERB + "grey_willow",	\
	          KRHERB + "hazelnut",		\
	          GOHERB + "holly",		\
	          GOHERB + "myrtle",		\
	          TRHERB + "whitehorn",		\
    }),  \
    "beach" :  ({ AVHERB + "bloodcreep",	\
		  KRHERB + "cladina",		\
		  AVHERB + "carlith",		\
		  KRHERB + "bch_plum",		\
		  KRHERB + "bch_willow",	\
		  KRHERB + "cattail",		\
		  KRHERB + "sargassum",		\
		  KRHERB + "elkhorn_kelp",	\
		  GOHERB + "mint",		\
		  AVHERB + "nethra",		\
		  KRHERB + "jewelweed",		\
		  KRHERB + "sea_bubble",	\
		  KRHERB + "ss_grass",		\
		  KRHERB + "sphagnum",		\
		  AVHERB + "strangleweed",      \
    }),  \
    "forest" : ({ KRHERB + "amanita",		\
		  KRHERB + "asparagus",		\
		  GOHERB + "attanar",		\
		  GOHERB + "astaldo", SHHERB + "bilberry",  \
          KALADHB +"blade",            \
          KRHERB + "blk_currant",	\
		  GOHERB + "blackberry",	\
		  AVHERB + "bloodcreep",	\
		  GOHERB + "blueberry",		\
		  GOHERB + "blung",		\
		  GOHERB + "braspberry",	\
		  AVHERB + "carlith",		\
		  AVHERB + "chartess",		\
		  KRHERB + "chicory",		\
		  KRHERB + "cladina",		\
		  KRHERB + "fdlhead",		\
		  AVHERB + "fordinfa",		\
		  KRHERB + "fireweed",		\
		  GOHERB + "foxglove",		\
		  KRHERB + "grey_willow",	\
		  SHHERB + "huckleberry",	\
		  KRHERB + "jewelweed",		\
		  GOHERB + "laurel",		\
		  GOHERB + "mint",		\
		  AVHERB + "nethra",		\
		  KRHERB + "onoclea",		\
		  TRHERB + "ramira",		\
		  GOHERB + "redweed",		\
		  AVHERB + "ronwath",		\
		  GOHERB + "seregon",		\
		  AVHERB + "shadow_onion",	\
		  AVHERB + "strangleweed",      \
		  GOHERB + "sumac",		\
		  GOHERB + "suranie",		\
		  GOHERB + "tuo",		\
		  TRHERB + "wilcol",		\
		  KRHERB + "wild_plum",		\
		  GOHERB + "wstrawberry",	\
    }),   \
    "dark" : ({   KRHERB + "amanita",		\
		  KRHERB + "angeltear",		\
		  GOHERB + "astaldo",		\
		  AVHERB + "bloodcreep",	\
                  KALADHB +"blade",             \
		  KRHERB + "brownslime",	\
		  KRHERB + "chantrelle",	\
		  AVHERB + "chartess",		\
		  KRHERB + "cladina",		\
		  AVHERB + "fordinfa",		\
		  GOHERB + "handasse",		\
		  AVHERB + "mittikna",		\
		  TRHERB + "moosho",		\
		  GOHERB + "tuo",		\
    }),   \
    "desert" : ({ GOHERB + "culkas",		\
		  KRHERB + "breadroot",		\
		  KRHERB + "crocus",		\
		  AVHERB + "shadow_onion",	\
		  KRHERB + "soapweed",		\
		  AVHERB + "strangleweed",      \
    }),   \
    "garden": ({  KRHERB + "asparagus",		\
		  AVHERB + "belladonna",	\
		  GOHERB + "blackberry",	\
		  KRHERB + "blk_currant",	\
		  GOHERB + "braspberry",	\
		  GOHERB + "caraway",		\
		  GOHERB + "carrot",		\
		  GOHERB + "carrot_wild",	\
		  GOHERB + "catnip",		\
		  GOHERB + "chervil",		\
		  KRHERB + "chokecherry",	\
		  GOHERB + "clove",		\
		  KRHERB + "crocus",		\
		  KRHERB + "dandelion",		\
		  GOHERB + "dill",		\
		  GOHERB + "fennel",		\
		  GOHERB + "garlic",		\
		  GOHERB + "ginger",		\
		  GOHERB + "gonion",		\
		  KRHERB + "hazelnut",		\
		  KRHERB + "hop",		\
		  SHHERB + "huckleberry",	\
		  GOHERB + "laurel",		\
		  KRHERB + "licorice",		\
		  GOHERB + "mint",		\
		  GOHERB + "oregano",		\
		  SHHERB + "parsley",		\
		  KRHERB + "raspberry",		\
		  GOHERB + "rosemary",		\
		  GOHERB + "saffron",		\
		  AVHERB + "shadow_onion",	\
		  GOHERB + "strawberry",	\
                  GOHERB + "tarragon",          \
    }),   \
    "jungle": ({  AVHERB + "bloodcreep",	\
		  KRHERB + "cladina",		\
		  AVHERB + "carlith",		\
		  AVHERB + "chartess",		\
		  KRHERB + "fdlhead",		\
		  GOHERB + "ginger",		\
		  GOHERB + "handasse",		\
		  AVHERB + "mittikna",		\
		  KRHERB + "onoclea",		\
		  AVHERB + "ronwath",		\
		  AVHERB + "strangleweed",	\
		  AVHERB + "shadow_onion",	\
		  TRHERB + "wilcol",		\
		  KRHERB + "wild_cuke",		\
    }),   \
    "pine": ({    KRHERB + "amanita",		\
		  GOHERB + "attanar",		\
		  GOHERB + "astaldo",		\
		  AVHERB + "belladonna",	\
                  SHHERB + "bilberry",          \
		  AVHERB + "bloodcreep",	\
		  GOHERB + "blueberry",		\
		  GOHERB + "blung",		\
		  KRHERB + "bunchberry",	\
		  AVHERB + "carlith",		\
		  KRHERB + "chantrelle",	\
		  AVHERB + "chartess",		\
		  KRHERB + "cladina",		\
		  GOHERB + "coccinea",		\
		  KRHERB + "cranberry",		\
		  GOHERB + "curugwath",		\
		  KRHERB + "fdlhead",		\
		  AVHERB + "fordinfa",		\
		  KRHERB + "grey_willow",	\
		  GOHERB + "holly",		\
		  GOHERB + "laurel",		\
		  GOHERB + "myrtle",		\
		  AVHERB + "narcissus",		\
		  KRHERB + "onoclea",		\
		  TRHERB + "ramira",		\
		  TRHERB + "sebre",		\
		  AVHERB + "shadow_onion",	\
		  KRHERB + "sphagnum",		\
		  GOHERB + "suranie",		\
		  SHHERB + "treemushroom",	\
		  GOHERB + "tuo",		\
    }),   \
    "river": ({   SHHERB + "adillyp",		\
		  KRHERB + "asparagus",		\
		  GOHERB + "blackberry",	\
		  GOHERB + "braspberry",	\
		  KRHERB + "bur_reed",		\
		  AVHERB + "carlith",		\
		  KRHERB + "cladina",		\
		  GOHERB + "curugwath",		\
		  KRHERB + "fdlhead",		\
		  AVHERB + "fordinfa",		\
		  KRHERB + "grey_willow",	\
		  KRHERB + "jewelweed",		\
		  GOHERB + "lothore",		\
		  KRHERB + "licorice",		\
		  TRHERB + "lukilvor",		\
		  GOHERB + "mint",		\
		  TRHERB + "moosho",		\
		  AVHERB + "nethra",		\
		  GOHERB + "suranie",		\
		  GOHERB + "tyelka",		\
		  TRHERB + "wilcol",		\
		  KRHERB + "wild_cuke",		\
		  GOHERB + "wstrawberry",	\
    }),   \
    "estuary": ({ AVHERB + "bloodcreep",	\
		  KRHERB + "cladina",		\
		  KRHERB + "eel_grass",		\
		  KRHERB + "fucus",		\
		  KRHERB + "fdlhead",		\
		  AVHERB + "fordinfa",		\
		  AVHERB + "nethra",		\
		  AVHERB + "carlith",		\
		  KRHERB + "sea_bubble",	\
		  KRHERB + "sphagnum",		\
		  TRHERB + "wilcol",            \
		  KRHERB + "sea_lettuce",	\
		  AVHERB + "strangleweed",      \
		  GOHERB + "tuo",		\
    }),   \
    "ocean": ({   KRHERB + "bull_kelp",		\
		  KRHERB + "elkhorn_kelp",	\
		  KRHERB + "laminaria",		\
		  TRHERB + "moosho",		\
		  AVHERB + "nethra",		\
		  KRHERB + "sargassum",		\
		  KRHERB + "sea_bubble",	\
    }),   \
    "swamp": ({   SHHERB + "adillyp",		\
                  GOHERB + "angurth",           \
		  KRHERB + "asparagus",		\
                  KALADHB +"blade",            \
		  GOHERB + "blueberry",		\
		  GOHERB + "blung",		\
		  KRHERB + "cattail",		\
		  AVHERB + "carlith",		\
		  KRHERB + "chicory",		\
                  GOHERB + "coccinea",          \
		  KRHERB + "cranberry",		\
		  GOHERB + "curugwath",		\
		  KRHERB + "fdlhead",		\
		  AVHERB + "fordinfa",		\
                  GOHERB + "frostheal",         \
                  KALADHB + "fungari",          \
		  KRHERB + "grey_willow",	\
		  KRHERB + "mandrake",		\
                  GOHERB + "simbelmyne",        \
		  KRHERB + "sphagnum",		\
		  AVHERB + "shadow_onion",	\
		  AVHERB + "strangleweed",      \
		  GOHERB + "suranie",		\
                  GOHERB + "sumac",             \
		  KRHERB + "wild_cuke",		\
		  TRHERB + "whitehorn", 	\
		  TRHERB + "wilcol",            \
    }),   \
])

/*
 * I have no idea why we need aliases
 * but they were a thing, so this exists.
 */
#define AREA_ALIAS ([ \
       "artic" : "arctic",	\
       "shore" : "beach",	\
    "seashore" : "beach",	\
      "boreal" : "forest",	\
        "cave" : "dark",	\
   "utterdark" : "dark",	\
      "stream" : "river",	\
   "riverbank" : "river",	\
   "saltmarsh" : "estuary",	\
	 "sea" : "ocean",	\
  "underwater" : "ocean",	\
  	 "bog" : "swamp",	\
       "marsh" : "swamp",	\
     "wetland" : "swamp",	\
])

