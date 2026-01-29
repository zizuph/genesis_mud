    /*
 *    /d/Gondor/common/herbs/herb_master.c
 *
 *    Copyright (c) 1995, 1996, 1997 by Henry Hardy and 
 *                      Christian Markus  
 *
 *    This object will return an array of herb names
 *    for different areatypes.
 *
 *    Olorin, November 1995
 *
 *    Modification log:
 *    17-Feb-1997, Olorin and Zephram:
 *            Added Krynn herbs to "forest",
 *            added herbs to "dunland",
 *            created "tolthar".
 */
#pragma save_binary
#pragma strict_types
#pragma no_clone

inherit "/std/object.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/common/herbs/include/herbs_bean.h"
#include "/d/Gondor/common/herbs/include/herbs_beet.h"
#include "/d/Gondor/common/herbs/include/herbs_carrot.h"
#include "/d/Gondor/common/herbs/include/herbs_fruit.h"

static string *herbs = HERBS,
              *bean_herb = BEAN_HERB,
              *carrot_herb = CARROT_HERBS,
              *fruit_herb = FRUIT_HERBS;

//            *beet_herb = BEET_HERB,

public void
create_object()
{
    set_name("herb master");
    add_name(({"master", }));
    set_adj("herb");
}

varargs string *
query_veto_herbs(mixed veto)
{
    int     i,
            s;
    string *veto_herbs = ({ });

    if (!veto)
        return ({ });

    if (stringp(veto))
        veto = ({ veto });

    for (i = 0, s = sizeof(veto); i < s; i++)
        switch (LOW(veto[i]))
        {
            case "middle earth":
                veto_herbs += ({ HERB_DIR + "alfirin", 
                 HERB_DIR + "athelas",
                                 HERB_DIR + "elanor",
                                 HERB_DIR + "handasse",
                                 HERB_DIR + "ithilgil",
                                 HERB_DIR + "lissuin",
                                 HERB_DIR + "niphredil",
                                                          });
                break;
            case "lorien":
                veto_herbs += ({ HERB_DIR + "elanor",
                                 HERB_DIR + "niphredil",
                                                          });
                break;
        }

    return veto_herbs;
}

varargs string *
query_herbs(mixed areatype, mixed veto)
{
    int     i,
            s;
    string *area_herbs = ({}),
           *add_veto = ({});

    if (!areatype)
    {
        if (veto)
            return (herbs - query_veto_herbs(veto));
        return herbs;
    }

    if (stringp(areatype))
        areatype = ({ areatype });

    for (i = 0, s = sizeof(areatype); i < s; i++)
        switch (LOW(areatype[i]))
        {
            // different topography
            case "desert":
                area_herbs += ({ HERB_DIR + "culkas" });
                break;
            case "eversnow":
                area_herbs += ({ HERB_DIR + "frostheal",
                                                          });
                break;
            case "jungle":
            case "forest":
                area_herbs += ({HERB_DIR + "attanar",
                                HERB_DIR + "astaldo",
                                SHIRE_HERB_DIR + "bilberry",
                                HERB_DIR + "blackberry",
                                SHIRE_HERB_DIR + "blackroot",
                                HERB_DIR + "blueberry",
                                HERB_DIR + "blung",
                                HERB_DIR + "coccinea",
                                HERB_DIR + "curugwath",
                                HERB_DIR + "foxglove",
                                SHIRE_HERB_DIR + "goats_rue",
                                HERB_DIR + "handasse",
                                HERB_DIR + "hemlock",
                                HERB_DIR + "holly",
                                SHIRE_HERB_DIR + "huckleberry",
                                SHIRE_HERB_DIR + "huckleberry",
                                HERB_DIR + "ithilgil",
                                SHIRE_HERB_DIR + "khuz",
                                HERB_DIR + "laurel",
                                HERB_DIR + "marigold",
                                SHIRE_HERB_DIR + "maroea",
                                HERB_DIR + "myrtle",
                                SHIRE_HERB_DIR + "pawnrose",
                                HERB_DIR + "raspberry",
                                HERB_DIR + "redweed",
                                HERB_DIR + "savory",
                                HERB_DIR + "sumac",
                                HERB_DIR + "suranie",
                                SHIRE_HERB_DIR + "treemushroom",
                                HERB_DIR + "tuo",
                                HERB_DIR + "ungolestel",
                                HERB_DIR + "wstrawberry",
                 KRYNN_HERB_DIR + "amanita",
                 KRYNN_HERB_DIR + "hawthorn",
                 KRYNN_HERB_DIR + "hazelnut",
                 KRYNN_HERB_DIR + "lady_slipper",
                 KRYNN_HERB_DIR + "poison_ivy",
                 KRYNN_HERB_DIR + "saskatoon",
                                                          });
                break;
        case "coniferous":
        break;
        case "deciduous":
        break;
            case "garden":
                area_herbs += ({HERB_DIR + "basil",
                                HERB_DIR + "blackberry",
                                HERB_DIR + "blueberry",
                                SHIRE_HERB_DIR + "calendula",
                                HERB_DIR + "catnip",
                                HERB_DIR + "chervil",
                                SHIRE_HERB_DIR + "chives",
                                HERB_DIR + "clove",
                                SHIRE_HERB_DIR + "columbine",
                                HERB_DIR + "dill",
                                HERB_DIR + "fennel",
                                HERB_DIR + "garlic",
                                HERB_DIR + "ginger",
                                HERB_DIR + "laurel",
                                HERB_DIR + "marigold",
                                HERB_DIR + "marjoram",
                                HERB_DIR + "mint",
                                SHIRE_HERB_DIR + "nasturtium",
                                HERB_DIR + "oregano",
                                SHIRE_HERB_DIR + "parsley",
                                HERB_DIR + "raspberry",
                                HERB_DIR + "red_pepper",
                                HERB_DIR + "rosemary",
                                HERB_DIR + "saffron",
                                HERB_DIR + "sage",
                                HERB_DIR + "savory",
                                HERB_DIR + "strawberry",
                                SHIRE_HERB_DIR + "tansy",
                                HERB_DIR + "tarragon",
                                HERB_DIR + "thyme",
                                SHIRE_HERB_DIR + "parsley",
                                                          });
                break;
            case "hills":
                area_herbs += ({HERB_DIR + "athelas",
                                SHIRE_HERB_DIR + "bilberry",
                                HERB_DIR + "blueberry",
                                SHIRE_HERB_DIR + "chives",
                                HERB_DIR + "hemlock",
                                HERB_DIR + "holly",
                                SHIRE_HERB_DIR + "huckleberry",
                                HERB_DIR + "ithilgil",
                                SHIRE_HERB_DIR + "laranthas",
                                HERB_DIR + "marigold",
                                SHIRE_HERB_DIR + "nasturtium",
                                SHIRE_HERB_DIR + "parsley",
                                HERB_DIR + "sage",
                                HERB_DIR + "savory",
                                HERB_DIR + "seregon",
                                SHIRE_HERB_DIR + "treemushroom",
                                                          });
                break;
            case "moderate":
                area_herbs += ({ HERB_DIR + "fennel",
                                 HERB_DIR + "garlic",
                                 HERB_DIR + "mint",
                                 HERB_DIR + "myrtle",
                                 HERB_DIR + "oregano",
                                 HERB_DIR + "tarragon",
                                                          });
                break;
            case "meadow":
                area_herbs += ({SHIRE_HERB_DIR + "bilberry", 
                                HERB_DIR + "bpotato",                          
                                SHIRE_HERB_DIR + "blackroot",
                                HERB_DIR + "caraway",
                                HERB_DIR + "catnip",
                                HERB_DIR + "chervil",
                                HERB_DIR + "coccinea",
                                SHIRE_HERB_DIR + "columbine",
                                HERB_DIR + "foxglove",
                                HERB_DIR + "garlic",
                                SHIRE_HERB_DIR + "grass",
                                SHIRE_HERB_DIR + "huckleberry",
                                SHIRE_HERB_DIR + "khuz",
                                SHIRE_HERB_DIR + "laranthas",
                                SHIRE_HERB_DIR + "lianor_berry",
                                HERB_DIR + "lissuin",
                                HERB_DIR + "lothore",
                                HERB_DIR + "marigold",
                                SHIRE_HERB_DIR + "nasturtium",
                                SHIRE_HERB_DIR + "pawnrose",
                                HERB_DIR + "rosemary",
                                HERB_DIR + "rpotato",
                                HERB_DIR + "saffron",
                                HERB_DIR + "sage",
                                HERB_DIR + "savory",
                                HERB_DIR + "tarragon",
                                HERB_DIR + "ungolestel",
                                                          });
                break;
            case "mountains":
                area_herbs += ({HERB_DIR + "frostheal",
                                HERB_DIR + "madwort",
                                                          });
                break;
            case "plains":
            case "plain":
                area_herbs += ({HERB_DIR + "alfirin",
                                SHIRE_HERB_DIR + "lamia",
                                SHIRE_HERB_DIR + "laranthas",
                                HERB_DIR + "caraway",
                                HERB_DIR + "marjoram",
                                HERB_DIR + "tarragon",
                                SHIRE_HERB_DIR + "parsley",
                                HERB_DIR + "basil",
                                HERB_DIR + "catnip",
                                HERB_DIR + "redweed",
                                HERB_DIR + "hemlock",
                                HERB_DIR + "fennel",
                                HERB_DIR + "chervil",
                                SHIRE_HERB_DIR + "chives",
                                SHIRE_HERB_DIR + "khuz",
                                HERB_DIR + "thyme",
                                SHIRE_HERB_DIR + "bilberry",
                                HERB_DIR + "dill",
                                HERB_DIR + "simbelmyne",
                                HERB_DIR + "mint",
                                HERB_DIR + "holly",
                                SHIRE_HERB_DIR + "columbine",
                                HERB_DIR + "gonion",
                                HERB_DIR + "rosemary",
                                HERB_DIR + "lothore",
                                HERB_DIR + "rpotato",
                                HERB_DIR + "bpotato",
                                SHIRE_HERB_DIR + "grass",
                                HERB_DIR + "oregano",

                                                          });
                break;
            case "subtropical":
                area_herbs += ({ HERB_DIR + "basil",
                                 HERB_DIR + "clove",
                                 HERB_DIR + "dill",
                                 HERB_DIR + "fennel",
                                 HERB_DIR + "garlic",
                                 HERB_DIR + "ginger",
                                 HERB_DIR + "laurel",
                                 HERB_DIR + "marjoram",
                                 HERB_DIR + "red_pepper",
                                 HERB_DIR + "rosemary",
                                 HERB_DIR + "saffron",
                                 HERB_DIR + "sage",
                                 HERB_DIR + "savory",
                                 HERB_DIR + "thyme",
                                                          });
            case "wetlands":
            case "swamp":
                area_herbs += ({SHIRE_HERB_DIR + "adillyp",
                                SHIRE_HERB_DIR + "calendula",
                                SHIRE_HERB_DIR + "chives",
                                SHIRE_HERB_DIR + "columbine",
                                HERB_DIR + "curugwath",
                                SHIRE_HERB_DIR + "daffodil",
                                HERB_DIR + "marigold",
                                SHIRE_HERB_DIR + "maroea",
                                SHIRE_HERB_DIR + "marshmallow",
                                SHIRE_HERB_DIR + "tansy",
                                HERB_DIR + "tyelka",

                                                          });
                break;
            // different continents
            case "dunland":
        // Annalda grows only on the island in the Greyflood
        // at Tharbad. It may not be added to this array.
                area_herbs += ({ HERB_DIR + "bpotato",
                                 HERB_DIR + "gonion",
                                 HERB_DIR + "rpotato",
                                 HERB_DIR + "bean_fava",
                                 HERB_DIR + "carrot_wild",
                                 HERB_DIR + "wstrawberry",
                                 HERB_DIR + "braspberry",
                                 HERB_DIR + "blackberry",
                                 HERB_DIR + "mint",
                                 HERB_DIR + "holly",
                                 HERB_DIR + "garlic",
                                 KRYNN_HERB_DIR + "dandelion",
                                 KRYNN_HERB_DIR + "hawthorn",
                                 KRYNN_HERB_DIR + "poison_ivy",
                                                          });
                break;
            case "tolthar":
                //This is the island in the Greyflood at Tharbad.
                area_herbs += ({ HERB_DIR + "annalda",
                                 HERB_DIR + "athelas",
                                 HERB_DIR + "blueberry",
                                 HERB_DIR + "caraway",
                                 HERB_DIR + "dill",
                                 HERB_DIR + "blung",
                                 HERB_DIR + "raspberry",
                                 HERB_DIR + "braspberry",
                                 HERB_DIR + "wstrawberry",
                                 HERB_DIR + "strawberry",
                                 KRYNN_HERB_DIR + "hawthorn",
                                 KRYNN_HERB_DIR + "jewelweed",
                                 KRYNN_HERB_DIR + "poison_ivy",
                                 KRYNN_HERB_DIR + "wild_cuke",
                                 KRYNN_HERB_DIR + "skullcap",
                                                          });
                break;
            case "ithilien":
                area_herbs += ({ HERB_DIR + "basil",
                                 HERB_DIR + "clove",
                                 HERB_DIR + "dill",
                                 HERB_DIR + "fennel",
                                 HERB_DIR + "garlic",
                                 HERB_DIR + "ginger",
                                 HERB_DIR + "laurel",
                                 HERB_DIR + "marigold",
                                 HERB_DIR + "marjoram",
                                 HERB_DIR + "rosemary",
                                 HERB_DIR + "saffron",
                                 HERB_DIR + "sage",
                                 HERB_DIR + "savory",
                                 HERB_DIR + "thyme",
                                 HERB_DIR + "tyelka",
                                                          });
                break;
            case "lebennin":
                area_herbs += ({ HERB_DIR + "alfirin",
                                                          });
                break;
            case "lorien":
                area_herbs += ({ HERB_DIR + "elanor",
                                 HERB_DIR + "niphredil",
                                                          });
                break;
            case "middle earth":
                area_herbs += ({ HERB_DIR + "alfirin",
                                 HERB_DIR + "angurth",
                                 HERB_DIR + "astaldo",
                                 HERB_DIR + "athelas",
                                 HERB_DIR + "handasse",
                                 HERB_DIR + "ithilgil",
                                 HERB_DIR + "lissuin",
                                 HERB_DIR + "marigold",
                                 HERB_DIR + "seregon",
                                 HERB_DIR + "simbelmyne",
                                 HERB_DIR + "tuo",
                                 HERB_DIR + "tyelka",
                                 HERB_DIR + "ungolestel",
                                                          });
                break;
            case "mordor":
                area_herbs += ({ HERB_DIR + "angurth",
                 HERB_DIR + "morgurth",
                                                          });
                break;
            // different types of herbs
            case "bean":
                area_herbs += bean_herb;
                break;
            case "beet":
//              area_herbs += beet_herb;
                break;
            case "carrot":
                area_herbs += carrot_herb;
                break;
            case "fruit":
                area_herbs += fruit_herb;
                break;
            default:
                break;
        }

    if (stringp(veto))
        veto = ({ veto });
    // remove double entries
    if (sizeof(veto))
    {
        add_veto -= veto;
        add_veto += veto;
    }
    if (sizeof(add_veto))
        area_herbs -= query_veto_herbs(add_veto);

    return area_herbs;
}
