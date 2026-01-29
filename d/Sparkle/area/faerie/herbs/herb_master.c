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

#ifndef GONDOR_HERB_DIR
#define GONDOR_HERB_DIR  "/d/Gondor/common/herbs/"
#endif
#ifndef SHIRE_HERB_DIR
#define SHIRE_HERB_DIR   "/d/Shire/common/herbs/"
#endif
#ifndef KRYNN_HERB_DIR
#define KRYNN_HERB_DIR   "/d/Krynn/common/herbs/"
#endif

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
        herb_files += ({ GONDOR_HERB_DIR + "attanar",
          GONDOR_HERB_DIR + "astaldo",
          GONDOR_HERB_DIR + "blueberry",
          GONDOR_HERB_DIR + "blung",
          GONDOR_HERB_DIR + "foxglove",
          GONDOR_HERB_DIR + "handasse",
          GONDOR_HERB_DIR + "hemlock",
          GONDOR_HERB_DIR + "holly",
          GONDOR_HERB_DIR + "laurel",
          GONDOR_HERB_DIR + "myrtle",
          GONDOR_HERB_DIR + "redweed",
          GONDOR_HERB_DIR + "savory",
          GONDOR_HERB_DIR + "sumac",
          GONDOR_HERB_DIR + "suranie",
          GONDOR_HERB_DIR + "tuo",
          GONDOR_HERB_DIR + "ungolestel",
          SHIRE_HERB_DIR + "bilberry",
          SHIRE_HERB_DIR + "blackroot",
          SHIRE_HERB_DIR + "huckleberry",
          SHIRE_HERB_DIR + "goats_rue",
          SHIRE_HERB_DIR + "khuz",
          SHIRE_HERB_DIR + "maroea",
          SHIRE_HERB_DIR + "pawnrose",
          SHIRE_HERB_DIR + "treemushroom",
          KRYNN_HERB_DIR + "amanita",
          KRYNN_HERB_DIR + "blk_currant",
          KRYNN_HERB_DIR + "bunchberry",
          KRYNN_HERB_DIR + "bkd_sedge",
          KRYNN_HERB_DIR + "chantrelle",
          KRYNN_HERB_DIR + "chicory",
          KRYNN_HERB_DIR + "cladina",
          KRYNN_HERB_DIR + "dandelion",
          KRYNN_HERB_DIR + "fdlhead",
          KRYNN_HERB_DIR + "fireweed",
          KRYNN_HERB_DIR + "grey_willow",
          KRYNN_HERB_DIR + "hawthorn",
          KRYNN_HERB_DIR + "hazelnut",
          KRYNN_HERB_DIR + "horsetail",
          KRYNN_HERB_DIR + "lady_slipper",
          KRYNN_HERB_DIR + "poison_ivy",
          KRYNN_HERB_DIR + "raspberry",
          KRYNN_HERB_DIR + "sarsaparilla",
          KRYNN_HERB_DIR + "tangleshoot",
          KRYNN_HERB_DIR + "tiger_lily",
          KRYNN_HERB_DIR + "wild_plum"
        });
        break;
    case "meadow":
        herb_files += ({ GONDOR_HERB_DIR + "bpotato",
          GONDOR_HERB_DIR + "caraway",
          GONDOR_HERB_DIR + "catnip",
          GONDOR_HERB_DIR + "chervil",
          GONDOR_HERB_DIR + "coccinea",
          GONDOR_HERB_DIR + "foxglove",
          GONDOR_HERB_DIR + "garlic",
          GONDOR_HERB_DIR + "ginger",
          GONDOR_HERB_DIR + "lissuin",
          GONDOR_HERB_DIR + "lothore",
          GONDOR_HERB_DIR + "marigold",
          GONDOR_HERB_DIR + "rosemary",
          GONDOR_HERB_DIR + "rpotato",
          GONDOR_HERB_DIR + "saffron",
          GONDOR_HERB_DIR + "sage",
          GONDOR_HERB_DIR + "savory",
          GONDOR_HERB_DIR + "tarragon",
          GONDOR_HERB_DIR + "ungolestel",
          SHIRE_HERB_DIR + "bilberry",
          SHIRE_HERB_DIR + "blackroot",
          SHIRE_HERB_DIR + "columbine",
          SHIRE_HERB_DIR + "grass",
          SHIRE_HERB_DIR + "khuz",
          SHIRE_HERB_DIR + "nasturtium",
          SHIRE_HERB_DIR + "laranthas",
          SHIRE_HERB_DIR + "pawnrose",
          SHIRE_HERB_DIR + "huckleberry",
          SHIRE_HERB_DIR + "lianor_berry",
          KRYNN_HERB_DIR + "chicory",
          KRYNN_HERB_DIR + "crocus",
          KRYNN_HERB_DIR + "dandelion",
          KRYNN_HERB_DIR + "horsetail",
          KRYNN_HERB_DIR + "locoweed",
          KRYNN_HERB_DIR + "sm_camas",
          KRYNN_HERB_DIR + "tiger_lily"
        });
        break;
    case "grasslands":
    case "grassland":
    case "field":
    case "plain":
    case "plains":
        herb_files += ({ GONDOR_HERB_DIR + "basil",
          GONDOR_HERB_DIR + "bpotato",
          GONDOR_HERB_DIR + "caraway",
          GONDOR_HERB_DIR + "catnip",
          GONDOR_HERB_DIR + "chervil",
          GONDOR_HERB_DIR + "dill",
          GONDOR_HERB_DIR + "fennel",
          GONDOR_HERB_DIR + "gonion",
          GONDOR_HERB_DIR + "hemlock",
          GONDOR_HERB_DIR + "holly",
          GONDOR_HERB_DIR + "lothore",
          GONDOR_HERB_DIR + "marigold",
          GONDOR_HERB_DIR + "marjoram",
          GONDOR_HERB_DIR + "mint",
          GONDOR_HERB_DIR + "oregano",
          GONDOR_HERB_DIR + "redweed",
          GONDOR_HERB_DIR + "rosemary",
          GONDOR_HERB_DIR + "rpotato",
          GONDOR_HERB_DIR + "simbelmyne",
          GONDOR_HERB_DIR + "tarragon",
          GONDOR_HERB_DIR + "thyme",
          SHIRE_HERB_DIR + "bilberry",
          SHIRE_HERB_DIR + "chives",
          SHIRE_HERB_DIR + "columbine",
          SHIRE_HERB_DIR + "khuz",
          SHIRE_HERB_DIR + "lamia",
          SHIRE_HERB_DIR + "laranthas",
          SHIRE_HERB_DIR + "parsley",
          SHIRE_HERB_DIR + "grass",
          KRYNN_HERB_DIR + "breadroot",
          KRYNN_HERB_DIR + "chicory",
          KRYNN_HERB_DIR + "cladina",
          KRYNN_HERB_DIR + "crocus",
          KRYNN_HERB_DIR + "dandelion",
          KRYNN_HERB_DIR + "fireweed",
          KRYNN_HERB_DIR + "grey_willow",
          KRYNN_HERB_DIR + "hawthorn",
          KRYNN_HERB_DIR + "horsetail",
          KRYNN_HERB_DIR + "locoweed",
          KRYNN_HERB_DIR + "poison_ivy",
          KRYNN_HERB_DIR + "raspberry",
          KRYNN_HERB_DIR + "saskatoon",
          KRYNN_HERB_DIR + "sm_camas",
          KRYNN_HERB_DIR + "tiger_lily"
        });
        break;
    case "hills":
    case "hill":
        herb_files += ({ GONDOR_HERB_DIR + "athelas",
          GONDOR_HERB_DIR + "blueberry",
          GONDOR_HERB_DIR + "hemlock",
          GONDOR_HERB_DIR + "holly",
          GONDOR_HERB_DIR + "frostheal",
          GONDOR_HERB_DIR + "madwort",
          GONDOR_HERB_DIR + "marigold",
          GONDOR_HERB_DIR + "savory",
          GONDOR_HERB_DIR + "seregon",
          SHIRE_HERB_DIR + "bilberry",
          SHIRE_HERB_DIR + "huckleberry",
          SHIRE_HERB_DIR + "laranthas",
          SHIRE_HERB_DIR + "nasturtium",
          SHIRE_HERB_DIR + "parsley",
          SHIRE_HERB_DIR + "treemushroom",
          SHIRE_HERB_DIR + "chives",
          KRYNN_HERB_DIR + "bkd_sedge",
          KRYNN_HERB_DIR + "cladina",
          KRYNN_HERB_DIR + "fireweed",
          KRYNN_HERB_DIR + "grey_willow",
          SHIRE_HERB_DIR + "khuz",
          KRYNN_HERB_DIR + "poison_ivy",
          KRYNN_HERB_DIR + "wild_plum"
        });
        break;
    case "woods":
        herb_files += ({ GONDOR_HERB_DIR + "athelas",
          GONDOR_HERB_DIR + "seregon",
          SHIRE_HERB_DIR + "bilberry",
          KRYNN_HERB_DIR + "soapweed",
          KRYNN_HERB_DIR + "fireweed"
        });
        break;

    case "stream":
    case "marsh":
    case "pond":
    case "river":
        herb_files += ({ GONDOR_HERB_DIR + "lothore",
          GONDOR_HERB_DIR + "blueberry",
          GONDOR_HERB_DIR + "coccinea",
          GONDOR_HERB_DIR + "ginger",
          GONDOR_HERB_DIR + "hemlock",
          GONDOR_HERB_DIR + "holly",
          GONDOR_HERB_DIR + "marigold",
          GONDOR_HERB_DIR + "sage",
          GONDOR_HERB_DIR + "savory",
          GONDOR_HERB_DIR + "seregon",
          GONDOR_HERB_DIR + "tyelka",
          SHIRE_HERB_DIR + "adillyp",
          SHIRE_HERB_DIR + "calendula",
          SHIRE_HERB_DIR + "chives",
          SHIRE_HERB_DIR + "columbine",
          SHIRE_HERB_DIR + "daffodil",
          SHIRE_HERB_DIR + "maroea",
          SHIRE_HERB_DIR + "marshmallow",
          SHIRE_HERB_DIR + "tansy",
          KRYNN_HERB_DIR + "bkd_sedge",
          KRYNN_HERB_DIR + "bur_reed",
          KRYNN_HERB_DIR + "cattail",
          KRYNN_HERB_DIR + "hop",
          KRYNN_HERB_DIR + "cranberry",
          KRYNN_HERB_DIR + "grey_willow",
          KRYNN_HERB_DIR + "hawthorn",
          KRYNN_HERB_DIR + "labr_tea",
          KRYNN_HERB_DIR + "mandrake",
          KRYNN_HERB_DIR + "sphagnum",
          KRYNN_HERB_DIR + "veronica",
          KRYNN_HERB_DIR + "wild_cuke",
          KRYNN_HERB_DIR + "cattail"
        });
        break;
    }
    }
    return herb_files;
}
