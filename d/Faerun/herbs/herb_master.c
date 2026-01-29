/*   Faerie Herb Master, based on the Shire Herb Master by Igneous
 *
 *   Created by using the Gondor Herb Master as an example.
 *   Major overhall and additional herbs added
 *   -- Finwe, March 2003
 *
 * Sept 07, 2003 - Palmer - Fixed the bug people were reporting
 * where they received no message after searching in some rooms.
 * Some arrays had a comment in the middle, which is a no-no.
 *
 * Sept 30, 2003 - Palmer - Fixed another bug where you get no
 *   message when searching for specific herbs. Make sure the
 *   herb file you have listed exists, otherwise it breaks search.
 *
 * April 31, 2004 - Finwe - Added Khuz, Laranthas, and Maroea herbs,
 * all from the old Rhovanion domain
 *
 * Modified from Shire's Herb Master originally by Igneous.
 * Thanks Igneous and Shire!! :)
 * By Finwe, August 2004

 */
#pragma save_binary
#pragma strict_types
#pragma no_clone

#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("herb master");
    add_name(({"master", }));
    set_adj("herb");
}


public string *
query_herbs(mixed *areatype)
{
    string *herb_files = ({});
    int i;

    if (!areatype)
        return herb_files;

    if (stringp(areatype))
        areatype = ({ areatype });

    for (i = 0; i < sizeof(areatype); i++)
    {
        switch(areatype[i])
        {
        case "forest":
        case "woods":
            herb_files += ({
                KRYNN_HERB_DIR  + "amanita",
                FAERUN_HERB_DIR + "angelica",
                GONDOR_HERB_DIR + "attanar",
                GONDOR_HERB_DIR + "angurth",
                SHIRE_HERB_DIR  + "bilberry",
                KRYNN_HERB_DIR  + "bkd_sedge",
                SHIRE_HERB_DIR  + "blackroot",
                KRYNN_HERB_DIR  + "blk_currant",
                GONDOR_HERB_DIR + "blueberry",
                FAERUN_HERB_DIR + "borage",
                KRYNN_HERB_DIR  + "bunchberry",
                KRYNN_HERB_DIR  + "chantrelle",
                KRYNN_HERB_DIR  + "chicory",
                KRYNN_HERB_DIR  + "cladina",
                KRYNN_HERB_DIR  + "dandelion",
                KRYNN_HERB_DIR  + "fdlhead",
                KRYNN_HERB_DIR  + "fireweed",
                GONDOR_HERB_DIR + "foxglove",
                SHIRE_HERB_DIR  + "goats_rue",
                KRYNN_HERB_DIR  + "grey_willow",
                KRYNN_HERB_DIR  + "hawthorn",
                KRYNN_HERB_DIR  + "hazelnut",
                GONDOR_HERB_DIR + "hemlock",
                KRYNN_HERB_DIR  + "horsetail",
                SHIRE_HERB_DIR  + "khuz",
                KRYNN_HERB_DIR  + "lady_slipper",
                GONDOR_HERB_DIR + "laurel",
                FAERUN_HERB_DIR + "lavender",
                SHIRE_HERB_DIR  + "maroea",
                GONDOR_HERB_DIR + "myrtle",
                GONDOR_HERB_DIR + "nettle",
                FAERUN_HERB_DIR + "oede",
                KRYNN_HERB_DIR  + "poison_ivy",
                KRYNN_HERB_DIR  + "raspberry",
                GONDOR_HERB_DIR + "redweed",
                KRYNN_HERB_DIR  + "sarsaparilla",
                KRYNN_HERB_DIR  + "soapweed",
                GONDOR_HERB_DIR + "sumac",
                GONDOR_HERB_DIR + "suranie",
                KRYNN_HERB_DIR  + "tangleshoot",
                KRYNN_HERB_DIR  + "tiger_lily",
                SHIRE_HERB_DIR  + "treemushroom",
                GONDOR_HERB_DIR + "ungolestel",
                KRYNN_HERB_DIR  + "wild_plum"
            });
            break;
        case "grasslands":
        case "grassland":
        case "field":
        case "plain":
        case "plains":
        case "meadow":
            herb_files += ({ 
                FAERUN_HERB_DIR + "amaranth",
                GONDOR_HERB_DIR + "basil",
                FAERUN_HERB_DIR + "bee_balm",
                GONDOR_HERB_DIR + "angurth",
                SHIRE_HERB_DIR  + "bilberry",
                SHIRE_HERB_DIR  + "blackroot",
                GONDOR_HERB_DIR + "bpotato",
                KRYNN_HERB_DIR  + "breadroot",
                GONDOR_HERB_DIR + "caraway",
                GONDOR_HERB_DIR + "catnip",
                KRYNN_HERB_DIR  + "chicory",
                SHIRE_HERB_DIR  + "chives",
                KRYNN_HERB_DIR  + "cladina",
                GONDOR_HERB_DIR + "coccinea",
                SHIRE_HERB_DIR  + "columbine",
                KRYNN_HERB_DIR  + "crocus",
                KRYNN_HERB_DIR  + "dandelion",
                GONDOR_HERB_DIR + "dill",
                GONDOR_HERB_DIR + "fennel",
                KRYNN_HERB_DIR  + "fireweed",
                GONDOR_HERB_DIR + "foxglove",
                GONDOR_HERB_DIR + "garlic",
                GONDOR_HERB_DIR + "ginger",
                GONDOR_HERB_DIR + "gonion",
                KRYNN_HERB_DIR  + "grey_willow",
                KRYNN_HERB_DIR  + "hawthorn",
                GONDOR_HERB_DIR + "hemlock",
                KRYNN_HERB_DIR  + "horsetail",
                SHIRE_HERB_DIR  + "khuz",
                SHIRE_HERB_DIR  + "lamia",
                SHIRE_HERB_DIR  + "laranthas",
                SHIRE_HERB_DIR  + "lianor_berry",
                FAERUN_HERB_DIR + "lobelia",
                KRYNN_HERB_DIR  + "locoweed",
                GONDOR_HERB_DIR + "marigold",
                GONDOR_HERB_DIR + "marjoram",
                GONDOR_HERB_DIR + "mint",
                SHIRE_HERB_DIR  + "nasturtium",
                GONDOR_HERB_DIR + "nettle",
                FAERUN_HERB_DIR + "oede",
                GONDOR_HERB_DIR + "oregano",
                SHIRE_HERB_DIR  + "parsley",
                KRYNN_HERB_DIR  + "poison_ivy",
                KRYNN_HERB_DIR  + "raspberry",
                GONDOR_HERB_DIR + "rosemary",
                GONDOR_HERB_DIR + "saffron",
                GONDOR_HERB_DIR + "sage",
                KRYNN_HERB_DIR  + "saskatoon",
                KRYNN_HERB_DIR  + "sm_camas",
                GONDOR_HERB_DIR + "thyme",
                KRYNN_HERB_DIR  + "tiger_lily",
                GONDOR_HERB_DIR + "ungolestel"
            });
            break;
        case "hills":
        case "hill":
            herb_files += ({
                SHIRE_HERB_DIR  + "bilberry",
                KRYNN_HERB_DIR  + "bkd_sedge",
                GONDOR_HERB_DIR + "blueberry",
                GONDOR_HERB_DIR + "angurth",
                SHIRE_HERB_DIR  + "chives",
                KRYNN_HERB_DIR  + "cladina",
                KRYNN_HERB_DIR  + "fireweed",
                GONDOR_HERB_DIR + "frostheal",
                KRYNN_HERB_DIR  + "grey_willow",
                GONDOR_HERB_DIR + "hemlock",
                SHIRE_HERB_DIR  + "khuz",
                SHIRE_HERB_DIR  + "laranthas",
                FAERUN_HERB_DIR + "lavender",
                FAERUN_HERB_DIR + "lobelia",
                GONDOR_HERB_DIR + "madwort",
                GONDOR_HERB_DIR + "nettle",
                GONDOR_HERB_DIR + "marigold",
                SHIRE_HERB_DIR  + "nasturtium",
                SHIRE_HERB_DIR  + "parsley",
                KRYNN_HERB_DIR  + "poison_ivy",
                GONDOR_HERB_DIR + "savory",
                GONDOR_HERB_DIR + "seregon",
                SHIRE_HERB_DIR  + "treemushroom",
                KRYNN_HERB_DIR  + "wild_plum"
            });
            break;
        case "stream":
        case "marsh":
        case "pond":
        case "river":
            herb_files += ({
                SHIRE_HERB_DIR  + "adillyp",
                KRYNN_HERB_DIR  + "bkd_sedge",
                GONDOR_HERB_DIR + "blueberry",
                GONDOR_HERB_DIR + "angurth",
                KRYNN_HERB_DIR  + "bur_reed",
                SHIRE_HERB_DIR  + "calendula",
                KRYNN_HERB_DIR  + "cattail",
                KRYNN_HERB_DIR  + "cattail",
                SHIRE_HERB_DIR  + "chives",
                GONDOR_HERB_DIR + "coccinea",
                SHIRE_HERB_DIR  + "columbine",
                KRYNN_HERB_DIR  + "cranberry",
                SHIRE_HERB_DIR  + "daffodil",
                GONDOR_HERB_DIR + "ginger",
                KRYNN_HERB_DIR  + "grey_willow",
                KRYNN_HERB_DIR  + "hawthorn",
                GONDOR_HERB_DIR + "hemlock",
                KRYNN_HERB_DIR  + "hop",
                GONDOR_HERB_DIR + "nettle",
                KRYNN_HERB_DIR  + "labr_tea",
                GONDOR_HERB_DIR + "marigold",
                SHIRE_HERB_DIR  + "maroea",
                SHIRE_HERB_DIR  + "marshmallow",
                GONDOR_HERB_DIR + "sage",
                KRYNN_HERB_DIR  + "sphagnum",
                SHIRE_HERB_DIR  + "tansy",
                KRYNN_HERB_DIR  + "veronica",
                KRYNN_HERB_DIR  + "wild_cuke"
            });
            break;
        case "underdark":
            herb_files += ({ 
                FAERUN_HERB_DIR + "adildra",
                FAERUN_HERB_DIR + "angel_tears",
                FAERUN_HERB_DIR + "bellarnon",
                FAERUN_HERB_DIR + "bloodfruit",
                GONDOR_HERB_DIR + "angurth",
                FAERUN_HERB_DIR + "carolden",
                FAERUN_HERB_DIR + "firemoss",
                FAERUN_HERB_DIR + "glowcap",
                FAERUN_HERB_DIR + "illavina",
                FAERUN_HERB_DIR + "lorea",
                FAERUN_HERB_DIR + "maicari",
                FAERUN_HERB_DIR + "marymoor",
                FAERUN_HERB_DIR + "osarni",
                FAERUN_HERB_DIR + "ranindir",
                FAERUN_HERB_DIR + "ripplebark",
                FAERUN_HERB_DIR + "selevon",
                FAERUN_HERB_DIR + "sun_stone",
                FAERUN_HERB_DIR + "sussur"
            });
            break;
        case "seacoast":
    /* This is for coastlines */
            herb_files += ({ 
                KRYNN_HERB_DIR    + "bch_plum",
                KRYNN_HERB_DIR    + "bch_willow",
                FAERUN_HERB_DIR   + "black_rush", 
                KRYNN_HERB_DIR    + "cord_grass",
                GONDOR_HERB_DIR + "angurth",
                EARTHSEA_HERB_DIR + "emmelti",
                FAERUN_HERB_DIR   + "gylvir", 
                KRYNN_HERB_DIR    + "mandrake",
                EARTHSEA_HERB_DIR + "nilgu",
                KRYNN_HERB_DIR    + "sargassum",
                FAERUN_HERB_DIR   + "sea_grape", 
                KRYNN_HERB_DIR    + "ss_grass",
                KRYNN_HERB_DIR    + "surf_grass"
            });
            break;
        case "saltwater":
    /* This for tidepools and in the seas, ie algaes, seaweed, kelp, etc. */
            herb_files += ({ 
                KRYNN_HERB_DIR  + "bull_kelp",
                KRYNN_HERB_DIR  + "coral_alga",
                FAERUN_HERB_DIR + "dm_fingers",
                KRYNN_HERB_DIR  + "eel_grass",
                FAERUN_HERB_DIR + "feather_boa_kelp",
                KRYNN_HERB_DIR  + "fucus",
                KRYNN_HERB_DIR  + "horn_kelp",
                KRYNN_HERB_DIR  + "laminaria",
                FAERUN_HERB_DIR + "red_algae",
                KRYNN_HERB_DIR  + "salt_wort",
                KRYNN_HERB_DIR  + "sea_bubble",
                KRYNN_HERB_DIR  + "sea_lettuce"
            });
            break;
        case "underground":
    //        herb_files += ({ });
            break;
        }
    }
    return herb_files;
}
