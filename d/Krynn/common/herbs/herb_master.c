/*
 *      modified from:
 *  /d/Gondor/common/herbs/herb_master.c
 *
 *  This object will return an array of herb names
 *  for different areatypes.
 *
 *  Olorin, November 1995
 *      modified by Teth for use in Krynn, November 1996
 *     removed veto_herbs functionality
 * Possible areatypes are desert, eversnow, jungle, mixedforest,
 * decidforest, conifforest, garden, hills, mountains,
 * meadow, plains, prairie, plain, shore, beach, sewer, cave,
 * intertide, nearshore, farshore, seabottom, oceanfloat,
 * urban, subtropical, wetlands, marsh, swamp, riverbank
 */
#pragma save_binary
#pragma strict_types
#pragma no_clone

inherit "/std/object.c";

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/herbs/herb_list.h"

static string *herbs = HERBS;

public void
create_object()
{
    set_name("herb master");
    add_name(({"master", }));
    set_adj("herb");
}

varargs string *
query_herbs(mixed areatype)
{
    int     i,
    s;
    string *area_herbs = ({});

    if (!areatype)
    {
        return herbs;
    }

    if (stringp(areatype))
        areatype = ({ areatype });

    for (i = 0, s = sizeof(areatype); i < s; i++)
        switch (L(areatype[i]))
    {
        // different topography
    case "desert":
        area_herbs += ({ GOHERB + "culkas",
          KRHERB + "breadroot",
          KRHERB + "crocus",
          KRHERB + "locoweed",
          KRHERB + "sm_camas",
          KRHERB + "soapweed",
        });
        break;
    case "eversnow":
        area_herbs += ({ GOHERB + "frostheal",
          KRHERB + "grey_willow",
          KRHERB + "hazelnut",
          GOHERB + "holly",
          GOHERB + "myrtle",
        });
        break;
    case "jungle":
        area_herbs += ({ KRHERB + "bkd_sedge",
          AVHERB + "carlith",
          KRHERB + "fdlhead",
          GOHERB + "ginger",
          KRHERB + "horsetail",
          AVHERB + "mittikna",
          KRHERB + "onoclea",
          AVHERB + "strangleweed",
        });
        break;
    case "mixedforest":
        area_herbs += ({ KRHERB + "asparagus",
          GOHERB + "attanar",
          GOHERB + "astaldo",
          KRHERB + "bkd_sedge",
          GOHERB + "blackberry",
          KRHERB + "blk_currant",
          GOHERB + "blueberry",
          GOHERB + "blung",
          GOHERB + "braspberry",
          KRHERB + "bunchberry",
          KRHERB + "chantrelle",
          KRHERB + "chicory",
          KRHERB + "chokecherry",
          KRHERB + "cladina",
          GOHERB + "coccinea",
          KRHERB + "dandelion",
          KRHERB + "elidross",
          KRHERB + "fdlhead",
          KRHERB + "fireweed",
          KHHERB + "green_pine",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          KRHERB + "hellebore",
          KRHERB + "hazelnut",
          KRHERB + "hop",
          KRHERB + "horsetail",
          SHHERB + "huckleberry",
          KRHERB + "lady_slipper",
          GOHERB + "laurel",
          KRHERB + "licorice",
          GOHERB + "mint",
          GOHERB + "myrtle",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          GOHERB + "redweed",
          KRHERB + "sarsaparilla",
          KRHERB + "saskatoon",
          KRHERB + "solinaith",
          GOHERB + "sumac",
          GOHERB + "suranie",
          KRHERB + "tangleshoot",
          KRHERB + "tiger_lily",
          SHHERB + "treemushroom",
          GOHERB + "tuo",
          GOHERB + "tyelka",
          GOHERB + "ungolestel",
          KRHERB + "wild_plum",
          GOHERB + "wstrawberry",
        });
        break;
    case "conifforest":
        area_herbs += ({ KRHERB + "amanita",
          GOHERB + "attanar",
          GOHERB + "astaldo",
          GOHERB + "blueberry",
          GOHERB + "blung",
          KRHERB + "bunchberry",
          KHHERB + "cedar_bark",
          KRHERB + "chantrelle",
          KRHERB + "chokecherry",
          KRHERB + "cladina",
          GOHERB + "coccinea",
          KRHERB + "cranberry",
          GOHERB + "curugwath",
          KRHERB + "elidross",
          KRHERB + "fdlhead",
          KHHERB + "green_pine",
          KRHERB + "grey_willow",
          KRHERB + "hazelnut",
          KRHERB + "hellebore",
          GOHERB + "holly",
          KRHERB + "horsetail",
          KRHERB + "labr_tea",
          KRHERB + "lady_slipper",
          GOHERB + "laurel",
          GOHERB + "myrtle",
          AVHERB + "narcissus",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "saskatoon",
          KRHERB + "solinaith",
          KRHERB + "sphagnum",
          GOHERB + "suranie",
          KRHERB + "tiger_lily",
          SHHERB + "treemushroom",
          GOHERB + "tuo",
          GOHERB + "ungolestel",
        });
        break;
    case "decidforest":
        area_herbs += ({ KRHERB + "amanita",
          KRHERB + "asparagus",
          GOHERB + "attanar",
          GOHERB + "astaldo",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          GOHERB + "blackberry",
          GOHERB + "blueberry",
          GOHERB + "blung",
          GOHERB + "braspberry",
          AVHERB + "carlith",
          KRHERB + "chicory",
          KRHERB + "chokecherry",
          KRHERB + "dandelion",
          KRHERB + "elidross",
          KRHERB + "fdlhead",
          KRHERB + "fireweed",
          GOHERB + "foxglove",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          KRHERB + "hellebore",
          KRHERB + "hazelnut",
          KRHERB + "hop",
          SHHERB + "huckleberry",
          KRHERB + "jewelweed",
          KRHERB + "lady_slipper",
          GOHERB + "laurel",
          KRHERB + "licorice",
          GOHERB + "mint",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          GOHERB + "redweed",
          AVHERB + "ronwath",
          KRHERB + "sarsaparilla",
          KRHERB + "saskatoon",
          GOHERB + "seregon",
          KRHERB + "solinaith",
          GOHERB + "sumac",
          GOHERB + "suranie",
          KRHERB + "tangleshoot",
          GOHERB + "tuo",
          GOHERB + "ungolestel",
          KRHERB + "veronica",
          KRHERB + "wild_plum",
          GOHERB + "wstrawberry",
        });
        break;

    case "garden":
        area_herbs += ({ KRHERB + "asparagus",
          GOHERB + "basil",
          GOHERB + "blackberry",
          KRHERB + "blk_currant",
          GOHERB + "braspberry",
          GOHERB + "caraway",
          GOHERB + "carrot",
          GOHERB + "carrot_wild",
          GOHERB + "catnip",
          GOHERB + "chervil",
          KRHERB + "chokecherry",
          GOHERB + "clove",
          KRHERB + "crocus",
          KRHERB + "dandelion",
          GOHERB + "dill",
          GOHERB + "fennel",
          GOHERB + "garlic",
          GOHERB + "ginger",
          GOHERB + "gonion",
          KRHERB + "hellebore",
          KRHERB + "hazelnut",
          KRHERB + "hop",
          SHHERB + "huckleberry",
          GOHERB + "laurel",
          KRHERB + "licorice",
          GOHERB + "marjoram",
          GOHERB + "mint",
          GOHERB + "oregano",
          SHHERB + "parsley",
          KRHERB + "raspberry",
          GOHERB + "red_pepper",
          GOHERB + "rosemary",
          GOHERB + "saffron",
          GOHERB + "sage",
          KRHERB + "saskatoon",
          GOHERB + "savory",
          GOHERB + "strawberry",
          GOHERB + "tarragon",
          GOHERB + "thyme",
          KRHERB + "tiger_lily",
          KRHERB + "wild_plum",
        });
        break;
    case "hills":
        area_herbs += ({ KRHERB + "bkd_sedge",
          GOHERB + "blackberry",
          GOHERB + "blueberry",
          KRHERB + "chokecherry",
          KRHERB + "cladina",
          KRHERB + "fireweed",
          KRHERB + "grey_willow",
          GOHERB + "holly",
          GOHERB + "sage",
          KRHERB + "saskatoon",
          GOHERB + "savory",
          GOHERB + "seregon",
          KRHERB + "wild_plum",
          GOHERB + "wstrawberry",
        });
        break;
    case "mountains":
        area_herbs += ({ KRHERB + "fireweed",
          GOHERB + "frostheal",
          GOHERB + "holly",
          GOHERB + "madwort",
        });
        break;
    case "meadow":
    case "plains":
    case "prairie":
    case "plain":
        area_herbs += ({ GOHERB + "basil",
          GOHERB + "blackberry",
          GOHERB + "bpotato",
          GOHERB + "braspberry",
          KRHERB + "breadroot",
          KRHERB + "hellebore",
          GOHERB + "caraway",
          GOHERB + "carrot_wild",
          GOHERB + "catnip",
          GOHERB + "chervil",
          KRHERB + "chicory",
          KRHERB + "cladina",
          GOHERB + "coccinea",
          KRHERB + "crocus",
          GOHERB + "culkas",
          KRHERB + "dandelion",
          GOHERB + "dill",
          GOHERB + "fennel",
          KRHERB + "fireweed",
          GOHERB + "foxglove",
          GOHERB + "garlic",
          GOHERB + "gonion",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          GOHERB + "hemlock",
          KRHERB + "horsetail",
          SHHERB + "huckleberry",
          KRHERB + "locoweed",
          GOHERB + "lothore",
          KRHERB + "licorice",
          GOHERB + "marjoram",
          GOHERB + "mint",
          AVHERB + "nightshade",
          GOHERB + "oregano",
          SHHERB + "parsley",
          SHHERB + "pawnrose",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          GOHERB + "redweed",
          GOHERB + "rosemary",
          GOHERB + "rpotato",
          GOHERB + "saffron",
          GOHERB + "sage",
          KRHERB + "saskatoon",
          GOHERB + "savory",
          KRHERB + "sm_camas",
          KRHERB + "soapweed",
          GOHERB + "tarragon",
          GOHERB + "thyme",
          KRHERB + "tiger_lily",
          GOHERB + "ungolestel",
          GOHERB + "wstrawberry",
        });
        break;
    case "shore":
    case "beach":
        area_herbs += ({ KRHERB + "bch_plum",
          KRHERB + "bch_willow",
          KRHERB + "cattail",
          KRHERB + "cord_grass",
          KRHERB + "dandelion",
          GOHERB + "hemlock",
          KRHERB + "horsetail",
          GOHERB + "mint",
          KRHERB + "poison_ivy",
          KRHERB + "salt_wort",
          KRHERB + "ss_grass",
        });
        break;
    case "sewer":
    case "cave":
        area_herbs += ({ KRHERB + "angeltear",
          KRHERB + "brownslime",
          KRHERB + "greenslime",
          KRHERB + "skullcap",
        });
        break;
    case "intertide":
    case "nearshore":
        area_herbs += ({ KRHERB + "coral_alga",
          KRHERB + "cord_grass",
          KRHERB + "eel_grass",
          KRHERB + "fucus",
          AVHERB + "nethra",
          KRHERB + "salt_wort",
          KRHERB + "sea_bubble",
          KRHERB + "sea_lettuce",
          KRHERB + "surf_grass",
        });
        break;
    case "seabottom":
    case "farshore":
        area_herbs += ({ KRHERB + "bull_kelp",
          KRHERB + "elkhorn_kelp",
          KRHERB + "laminaria",
          KRHERB + "sea_bubble",
        });
        break;
    case "oceanfloat":
        area_herbs += ({ KRHERB + "sargassum",
        });
        break;
    case "urban":
        area_herbs += ({ GOHERB + "blackberry",
          GOHERB + "braspberry",
          KRHERB + "chicory",
          KRHERB + "dandelion",
          GOHERB + "dill",
          GOHERB + "gonion",
          KRHERB + "hazelnut",
          KRHERB + "licorice",
          GOHERB + "mint",
          KRHERB + "raspberry",
          GOHERB + "rpotato",
          AVHERB + "ronwath",
          KRHERB + "saskatoon",
          GOHERB + "strawberry",
          KRHERB + "wild_plum",
        });
        break;
    case "subtropical":
        area_herbs += ({ GOHERB + "basil",
          AVHERB + "carlith",
          GOHERB + "clove",
          GOHERB + "dill",
          GOHERB + "fennel",
          GOHERB + "garlic",
          GOHERB + "ginger",
          KRHERB + "lady_slipper",
          GOHERB + "laurel",
          GOHERB + "marjoram",
          AVHERB + "mittikna",
          KRHERB + "onoclea",
          GOHERB + "red_pepper",
          GOHERB + "rosemary",
          GOHERB + "saffron",
          GOHERB + "sage",
          GOHERB + "savory",
          GOHERB + "thyme",
          KRHERB + "wild_cuke",
        });
    case "wetlands":
    case "marsh":
    case "swamp":
        area_herbs += ({ SHHERB + "adillyp",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          GOHERB + "blackberry",
          GOHERB + "blueberry",
          GOHERB + "blung",
          GOHERB + "braspberry",
          KRHERB + "bur_reed",
          KRHERB + "cattail",
          KHHERB + "cedar_bark",
          KRHERB + "cranberry",
          GOHERB + "curugwath",
          KHHERB + "green_pine",
          KRHERB + "grey_willow",
          GOHERB + "hemlock",
          KRHERB + "labr_tea",
          KRHERB + "mandrake",
          GOHERB + "mint",
          AVHERB + "narcissus",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "sphagnum",
          GOHERB + "ungolestel",
          KRHERB + "veronica",
          KRHERB + "wild_cuke",
        });
        break;
    case "riverbank":
        area_herbs += ({ SHHERB + "adillyp",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          GOHERB + "blackberry",
          GOHERB + "braspberry",
          KRHERB + "bur_reed",
          AVHERB + "carlith",
          GOHERB + "carrot_wild",
          KRHERB + "cattail",
          KRHERB + "chokecherry",
          GOHERB + "curugwath",
          GOHERB + "dill",
          KRHERB + "grey_willow",
          GOHERB + "hemlock",
          KRHERB + "hop",
          KRHERB + "horsetail",
          KRHERB + "jewelweed",
          GOHERB + "lothore",
          GOHERB + "mint",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "saskatoon",
          GOHERB + "suranie",
          GOHERB + "tyelka",
          KRHERB + "wild_cuke",
          GOHERB + "wstrawberry",
        });
        break;
    }

    return area_herbs;
}





