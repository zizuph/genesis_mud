/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
 * Changed exit reference to reflect directory structure
 * change.  Ckrik 1-25-98
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
    set_long("The path enters the dark evergreen forest " +
        "which climbs the flank of the mountain to the northeast. " +
        "The crisp air is scented with pine, and the terrain is " +
        "quite steep here. You turn south and gaze for a moment over the " +
        "vast expanse of dark blue sea in the distance, where " +
        "waves crash onto a sandy white beach. The water is dark " +
        "as wine where it is deep and becomes a blue haze where " +
        "it meets the horizon. Far down to the southwest you see " +
        "the dark walls and towers of Gont Port, where colourful " +
        "ships come and go. To the south a path descends " +
        "toward the beach area.\n");
    add_item((({"farmland", "pastures", "rolling hillside",
        "hillside"})),
        "There are farm cottages dotting the hillside with green " +
        "pasture and cultivated fields lying between them. Although " +
        "all should seem like a lovely view, you notice that something " +
        "is quite wrong... You see flame and plumes of smoke " +
        "rising from some of them.\n");
    add_item((({"Gont Port", "city", "dark walls", "towers"})),
        "The dark towers of Gont Port catch your gaze far below.\n");
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
    add_item((({"boulders", "brush"})),
        "Large boulders of granite and branches fallen from trees " +
        "block the path to the northeast, almost as though it were " +
        "intentional ...\n");
    add_exit("south_path_23", "northeast");
    add_exit("south_path_25", "southwest");
    add_exit("/d/Earthsea/gont/beach/forest_path_rooms/forest_path06",
        "south");
}
