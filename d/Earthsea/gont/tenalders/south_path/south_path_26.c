/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>

public void
create_herb_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("Mountain path");
    set_long("A few sparse evergreen trees mark the beginning of an " +
        "ancient evergreen forest that climbs the flank of the " +
        "mountain. The crisp air is scented with " +
        "pine, and the terrain becomes more rugged. Away down the " +
        "mountain to the south you see in the distance the vast " +
        "expanse of sea, where the waves crash onto a sandy " +
        "white beach. To the west you see green farmland and " +
        "pastures on the rolling hillside. Downwards to the west is " +
        "a wooden bridge and to the east the path continues to " +
        "climb steeply toward the darker forest.\n");
    add_item((({"farmland", "pastures", "rolling hillside",
        "hillside"})),
        "There are farm cottages dotting the hillside with green " +
        "pasture and cultivated fields lying between them. Although " +
        "all should seem like a lovely view, you notice that something " +
        "is quite wrong... You see flame and plumes of smoke " +
        "rising from some of them.\n");
    add_item((({"Gont City", "City", "white towers", "towers"})),
        "The white towers of Gont still glisten in the sun, with " +
        "boats going to and fro in the harbour. Away to the " +
        "southeast off the beach, however, you also make out " +
        "three black longships, with the red mark of Karego At on " +
        "their sails.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The pine forest climbs the flank of the mountain.\n");
    add_item((({"south", "sea", "beach", "white sandy beach",
        "sandy beach"})),
        "From this vantage point you view at a distance the vast " +
        "sea and the white beach far below.\n");
    add_item((({"pine needles", "needles", "path", "rugged path",
        "tangled undergrowth", "undergrowth", "rocks"})),
        "Dense forest undergrowth prevents your leaving the rugged " +
        "path, and pine needles crunch under your feet as you walk.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("bridge", "west");
    add_exit("south_path_25", "east");
}
