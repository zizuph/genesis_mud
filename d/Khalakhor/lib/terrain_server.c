/* File         : /d/Khalakhor/std/herbs/terrain_server.c
 * Creator      : Olorin and Zephram@Genesis
 * Date         : 199?         
 * Purpose      : This object will return an array of herb names
 *                for different terrain types.
 * Related Files: /d/Gondor/common/herbs/herb_master.c (original file)
 * Comments     :
 * Modifications: Nov-1996 Teth
 *                Modified for use in Krynn - removed veto_herbs
 *                functionality.
 *                Dec-17-1997 Teth
 *                Modified for use in Khalakhor, including old Khalakhor
 *                terrain type properties.
 *                Feb-05-2002 Teth
 *                Updated to use new mudlib terrain types.
 */

#pragma save_binary
#pragma strict_types
#pragma no_clone

inherit "/std/object.c";

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrain.h"

static string *herbs = ({ });

public void
create_object()
{
    set_name("terrain server");
    add_name(({"server", }));
    set_adj("herb");
}

varargs string *
query_herbs(mixed areatype)
{
    int     i,
    s;
    string *area_herbs = ({});

    // Never any herbs in the default terrain room.
    if (!areatype)
    {
        return herbs;
    }

    if (intp(areatype))
        areatype = ({ areatype });

    for (i = 0, s = sizeof(areatype); i < s; i++)
        switch (areatype[i])
    {

// Water geography cases!
    case TERRAIN_OCEAN:
    // Herbs found floating in the ocean.
        area_herbs += ({ KRHERB + "sargassum",
        });
        break;
    case TERRAIN_UNDERSEA:
    // Herbs found underwater in the open ocean.
        area_herbs += ({ KRHERB + "bull_kelp",
        KRHERB + "elkhorn_kelp",
        KRHERB + "laminaria",
        });
        break;
    case TERRAIN_BAY:
    // Herbs found floating in bays.
        area_herbs += ({ KRHERB + "sargassum",
        });
        break;
    case TERRAIN_LAKE:
    // Herbs found in lakes.
        area_herbs += ({
        });
        break;
    case TERRAIN_UNDERLAKE:
    // Herbs found underwater in lakes.
        area_herbs += ({
        });
        break;
    case TERRAIN_POND:
    // Herbs found in ponds.
        area_herbs += ({
        });
        break;
    case TERRAIN_RIVER:
    // Herbs found in rivers.
        area_herbs += ({
        });
        break;
    case TERRAIN_STREAM:
    // Herbs found in streams.
        area_herbs += ({ KRHERB + "cattail",
        });
        break;
// Natural outside environment cases!
    case TERRAIN_PLAIN:
    // Herbs found in grassy lowland flat areas.
        area_herbs += ({ GOHERB + "foxglove",
          KHHERB + "beatha",
          KRHERB + "breadroot",
          KRHERB + "chicory",
          KRHERB + "crocus",
          KRHERB + "dandelion",
          KRHERB + "hawthorn",
          KRHERB + "horsetail",
          KRHERB + "locoweed",
          KRHERB + "licorice",
          KRHERB + "saskatoon",
          KRHERB + "sm_camas",
          KRHERB + "tiger_lily",
        });
        break;
    case TERRAIN_MOOR:
    // Herbs found lowland flat areas, that have soil too poor for grasses.
        area_herbs += ({ GOHERB + "foxglove",
          GOHERB + "mint",
          KHHERB + "shamrock",
          KRHERB + "chicory",
          KRHERB + "dandelion",
        });
        break;
    case TERRAIN_GLACIER:
    // Herbs found on and near glaciers, near ice sheets.
        area_herbs += ({ GOHERB + "frostheal",
          GOHERB + "madwort",
        });
        break;
    case TERRAIN_TUNDRA:
    // Herbs found in open tundra area, cold polar and flat.
        area_herbs += ({
        });
        break;
    case TERRAIN_DESERT:
    // Herbs found in sandy areas.
        area_herbs += ({ GOHERB + "culkas",
          KRHERB + "soapweed",
        });
        break;
    case TERRAIN_SCRUB:
    // Herbs found in sandy flat areas with vegetative cover.
        area_herbs += ({ GOHERB + "culkas",
          GOHERB + "foxglove",
          KRHERB + "breadroot",
          KRHERB + "hawthorn",
          KRHERB + "locoweed",
          KRHERB + "soapweed",
          KRHERB + "sm_camas",
        });
        break;
    case TERRAIN_BADLAND:
    // Herbs found in sandy and rocky areas with vegetative cover.
        area_herbs += ({ GOHERB + "culkas",
          KRHERB + "locoweed",
          KRHERB + "soapweed",
        });
        break;
    case TERRAIN_WASTELAND:
    // Herbs found in sandy and rocky bare areas.
        area_herbs += ({ AVHERB + "nightshade",
          GOHERB + "culkas",
        });
        break;
    case TERRAIN_MOUNTAIN:
    // Herbs found on nonforested mountains.
        area_herbs += ({ GOHERB + "frostheal",
          GOHERB + "madwort",
          KRHERB + "fireweed",
        });
        break;
    case TERRAIN_HILL:
    // Herbs found on nonforested hills, includes highlands.
        area_herbs += ({ GOHERB + "blackberry",
          GOHERB + "foxglove",
          GOHERB + "madwort",
          KRHERB + "blk_currant",
          KRHERB + "fireweed",
          KRHERB + "grey_willow",
          KRHERB + "saskatoon",
          KRHERB + "wild_plum",
        });
        break;
    case TERRAIN_CLIFF:
    // Herbs found on cliffsides.
        area_herbs += ({ KRHERB + "fireweed",
        });
        break;
    case TERRAIN_VOLCANO:
    // Herbs found in a volcanic area.
        area_herbs += ({
        });
        break;
    case TERRAIN_LAKESHORE:
    // Herbs found along a rocky freshwater coast.
        area_herbs += ({ GOHERB + "hemlock",
          GOHERB + "mint",
          KHHERB + "green_pine",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "cattail",
          KRHERB + "fdlhead",
          KRHERB + "grey_willow",
          KRHERB + "horsetail",
          KRHERB + "jewelweed",
          KRHERB + "onoclea",
          KRHERB + "saskatoon",
        });
        break;
    case TERRAIN_COAST:
    // Herbs found along a rocky saltwater coast.
        area_herbs += ({ KRHERB + "coral_alga",
          KRHERB + "cord_grass",
          KRHERB + "eel_grass",
          KRHERB + "fucus",
          KRHERB + "salt_wort",
          KRHERB + "sea_bubble",
          KRHERB + "sea_lettuce",
          KRHERB + "surf_grass",
        });
        break;
    case TERRAIN_RIVERBANK:
    // Herbs found along a muddy or sandy riverbank.
        area_herbs += ({ AVHERB + "narcissus",
          GOHERB + "blackberry",
          GOHERB + "foxglove",
          GOHERB + "hemlock",
          GOHERB + "mint",
          KHHERB + "shamrock",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "bur_reed",
          KRHERB + "cattail",
          KRHERB + "chicory",
          KRHERB + "dandelion",
          KRHERB + "fdlhead",
          KRHERB + "grey_willow",
          KRHERB + "hop",
          KRHERB + "horsetail",
          KRHERB + "jewelweed",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "saskatoon",
          KRHERB + "wild_cuke",
        });
        break;
    case TERRAIN_SALTBEACH:
    // Herbs found on a sandy saltwater beach.
        area_herbs += ({ KRHERB + "bch_plum",
          KRHERB + "bch_willow",
          KRHERB + "bkd_sedge",
          KRHERB + "cord_grass",
          KRHERB + "salt_wort",
          KRHERB + "ss_grass",
        });
        break;
    case TERRAIN_FRESHBEACH:
    // Herbs found on a sandy freshwater beach.
        area_herbs += ({ GOHERB + "hemlock",
          GOHERB + "mint",
          KRHERB + "asparagus",
          KRHERB + "bch_plum",
          KRHERB + "bch_willow",
          KRHERB + "bkd_sedge",
          KRHERB + "bur_reed",
          KRHERB + "cattail",
          KRHERB + "horsetail",
          KRHERB + "poison_ivy",
        });
        break;
    case TERRAIN_SWAMP:
    // Herbs found in a forested water area.
        area_herbs += ({ KHHERB + "cedar_bark",
          KHHERB + "green_pine",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "mandrake",
        });
        break;
    case TERRAIN_MARSH:
    // Herbs found in an shallow somewhat open water area.
        area_herbs += ({ GOHERB + "mint",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "bur_reed",
          KRHERB + "cattail",
          KRHERB + "grey_willow",
          KRHERB + "jewelweed",
          KRHERB + "veronica",
          KRHERB + "wild_cuke",
        });
        break;
    case TERRAIN_BOG:
    // Herbs found in mossy forested areas, with the occasional open water.
        area_herbs += ({ KHHERB + "cedar_bark",
          KHHERB + "green_pine",
          KRHERB + "blk_currant",
          KRHERB + "cattail",
          KRHERB + "cladina",
          KRHERB + "cranberry",
          KRHERB + "fireweed",
          KRHERB + "grey_willow",
          KRHERB + "hazelnut",
          KRHERB + "labr_tea",
          KRHERB + "lady_slipper",
          KRHERB + "raspberry",
          KRHERB + "sarsaparilla",
          KRHERB + "sphagnum",
        });
        break;
    case TERRAIN_THICKET:
    // Herbs found in a _thick_ forested area, usually shrubs.
        area_herbs += ({ GOHERB + "blackberry",
          GOHERB + "mint",
          KHHERB + "cedar_bark",
          KHHERB + "shamrock",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "bur_reed",
          KRHERB + "cattail",
          KRHERB + "chokecherry",
          KRHERB + "fdlhead",
          KRHERB + "grey_willow",
          KRHERB + "hazelnut",
          KRHERB + "horsetail",
          KRHERB + "jewelweed",
          KRHERB + "lady_slipper",
          KRHERB + "raspberry",
          KRHERB + "saskatoon",
          KRHERB + "veronica",
        });
        break;
    case TERRAIN_BUSH:
    // Herbs found in area that is a mix of plains and forests. 
        area_herbs += ({ AVHERB + "nightshade",
          GOHERB + "blackberry",
          GOHERB + "foxglove",
          GOHERB + "mint",
          KHHERB + "green_pine",
          KRHERB + "amanita",
          KRHERB + "breadroot",
          KRHERB + "chicory",
          KRHERB + "chokecherry",
          KRHERB + "crocus",
          KRHERB + "dandelion",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          KRHERB + "lady_slipper",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "sarsaparilla",
          KRHERB + "saskatoon",
          KRHERB + "sm_camas",
          KRHERB + "tiger_lily",
        });
        break;
    case TERRAIN_JUNGLE:
    // Herbs found in tropical jungles.
        area_herbs += ({ KRHERB + "bkd_sedge",
          KRHERB + "horsetail",
        });
        break;
    case TERRAIN_MIXEDWOOD:
    // Herbs found in mixed woods forests.
        area_herbs += ({ GOHERB + "blackberry",
          KHHERB + "green_pine",
          KHHERB + "shamrock",
          KRHERB + "amanita",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "bunchberry",
          KRHERB + "chantrelle",
          KRHERB + "chicory",
          KRHERB + "chokecherry",
          KRHERB + "cladina",
          KRHERB + "dandelion",
          KRHERB + "fdlhead",
          KRHERB + "fireweed",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          KRHERB + "hazelnut",
          KRHERB + "hop",
          KRHERB + "horsetail",
          KRHERB + "lady_slipper",
          KRHERB + "licorice",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "sarsaparilla",
          KRHERB + "saskatoon",
          KRHERB + "tangleshoot",
          KRHERB + "tiger_lily",
          KRHERB + "wild_plum",
        });
        break;
    case TERRAIN_CONIFEROUS:
    // Herbs found in coniferous (evergreen) forests.
        area_herbs += ({ KHHERB + "cedar_bark", 
          KHHERB + "green_pine",
          KRHERB + "amanita",
          KRHERB + "bunchberry",
          KRHERB + "chantrelle",
          KRHERB + "chokecherry",
          KRHERB + "cladina",
          KRHERB + "cranberry",
          KRHERB + "crocus",
          KRHERB + "fdlhead",
          KRHERB + "grey_willow",
          KRHERB + "hazelnut",
          KRHERB + "horsetail",
          KRHERB + "labr_tea",
          KRHERB + "lady_slipper",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "saskatoon",
          KRHERB + "sphagnum",
          KRHERB + "tiger_lily",
        });
        break;
    case TERRAIN_DECIDUOUS:
    // Herbs found in deciduous (non-evergreen) forests.
        area_herbs += ({ GOHERB + "blackberry",
          GOHERB + "foxglove",
          GOHERB + "mint",
          KHHERB + "shamrock",
          KRHERB + "amanita",
          KRHERB + "asparagus",
          KRHERB + "bkd_sedge",
          KRHERB + "blk_currant",
          KRHERB + "chicory",
          KRHERB + "chokecherry",
          KRHERB + "dandelion",
          KRHERB + "fdlhead",
          KRHERB + "fireweed",
          KRHERB + "grey_willow",
          KRHERB + "hawthorn",
          KRHERB + "hazelnut",
          KRHERB + "hop",
          KRHERB + "jewelweed",
          KRHERB + "lady_slipper",
          KRHERB + "licorice",
          KRHERB + "onoclea",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "sarsaparilla",
          KRHERB + "saskatoon",
          KRHERB + "tangleshoot",
          KRHERB + "veronica",
          KRHERB + "wild_plum",
        });
        break;

// Underground cases!
    case TERRAIN_NCAVETUNNEL:
    // Herbs found in natural cave tunnels, molds and fungi.
        area_herbs += ({ KRHERB + "angeltear",
          KRHERB + "brownslime",
        });
        break;
    case TERRAIN_NCAVE:
    // Herbs found in natural caves, typically molds and fungi.
        area_herbs += ({ KRHERB + "brownslime",
          KRHERB + "skullcap",
        });
        break;
    case TERRAIN_NCAVELAKESH:
    // Herbs found alongside lakeshores in natural caves, what do you
    // think Gollum ate?
        area_herbs += ({ KRHERB + "angeltear",
          KRHERB + "brownslime",
          KRHERB + "greenslime",
          KRHERB + "skullcap",
        });
        break;
    case TERRAIN_NCAVEMAGMA:
    // Herbs found in natural caves with magma.
        area_herbs += ({
        });
        break;
    case TERRAIN_MINE:
    // Herbs found in mines, typically molds and fungi.
        area_herbs += ({
        });
        break;
    case TERRAIN_ARTOPENLAVA:
    // Herbs found in artifical open underground areas that have lava. 
        area_herbs += ({
        });
        break;

//Artificial area cases, those which are constructed somehow.
    case TERRAIN_ROAD:
    // Herbs found on roads, always weedy or common.
        area_herbs += ({ GOHERB + "foxglove",
          KRHERB + "chicory",
          KRHERB + "dandelion", 
        });
        break;
    case TERRAIN_STREET:
    // Herbs found alongside streets, always weedy or common.
        area_herbs += ({ KRHERB + "dandelion",
        });
        break;
    case TERRAIN_FIELD:
    // Herbs found in fields, weeds and grains.
        area_herbs += ({ KRHERB + "chicory",          
          KRHERB + "dandelion",
        });
        break;
    case TERRAIN_GARDEN:
    // Herbs found in gardens, common vegetables and such.
        area_herbs += ({ GOHERB + "blackberry",          
          GOHERB + "catnip",
          GOHERB + "caraway",
          GOHERB + "dill",
          GOHERB + "fennel",
          GOHERB + "marjoram",
          GOHERB + "mint",
          GOHERB + "oregano",
          GOHERB + "rosemary",
          GOHERB + "sage",
          GOHERB + "thyme",
          KHHERB + "shamrock",
          KRHERB + "asparagus",
          KRHERB + "chokecherry",
          KRHERB + "dandelion",
          KRHERB + "raspberry",
          SHHERB + "parsley",
        });
        break;
    case TERRAIN_GRAVEYARD:
    // Herbs found in graveyards!
        area_herbs += ({ KRHERB + "amanita",          
          KRHERB + "mandrake",
        });
        break;
    case TERRAIN_SEWER:
    // Herbs found in sewers, typically slimes and molds.
        area_herbs += ({ KRHERB + "angeltear",
          KRHERB + "brownslime",
          KRHERB + "greenslime",
          KRHERB + "skullcap",
        });
        break;
    case TERRAIN_PATH:
    // Herbs found along outdoor paths, typically weedy.
        area_herbs += ({ AVHERB + "nightshade",
          GOHERB + "blackberry",
          GOHERB + "foxglove",
          GOHERB + "ginger",
          GOHERB + "mint",
          KRHERB + "blk_currant",
          KRHERB + "bunchberry",
          KRHERB + "chicory",
          KRHERB + "crocus",
          KRHERB + "dandelion",
          KRHERB + "hazelnut",
          KRHERB + "poison_ivy",
          KRHERB + "raspberry",
          KRHERB + "saskatoon",
        });
        break;
    case TERRAIN_RUINS:
    // Herbs found in outdoor ruins, typically weedy.
        area_herbs += ({ AVHERB + "nightshade",
          GOHERB + "foxglove",
          KRHERB + "dandelion",
        });
        break;
    case TERRAIN_INRUINS:
    // Herbs such as fungi or molds found in indoor ruins.
        area_herbs += ({
        });
        break;
    case TERRAIN_TOMB:
    // Herbs such as fungi or molds found in tombs.
        area_herbs += ({
        });
        break;
    default:
        break;
    }

    return area_herbs;
}




