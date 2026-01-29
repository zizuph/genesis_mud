/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";
inherit "/d/Earthsea/gont/tenalders/sys/river_water";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>

public void
create_herb_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("Mountain path");
    set_long("A mountain path. You are walking along a " +
        "whitewater river, the Ar, that rushes down the steep mountain. " +
        "The path runs along a riverbank, and to the west is a " +
        "thick forest with tall ancient pine trees. " +
        "To the southwest the path turns away from the river " +
        "and enters the evergreen forest.\n");
    add_item((({"water", "whitewater", "whitewater river",
        "Ar", "river"})),
        "The river Ar rushes down the steep mountainside, its waters " +
        "cold, white, and frothy from melted snow.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The old forest towers to the west of you, ascending the " +
        "steep mountain.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_5", "northwest");
    add_exit("south_path_7", "southwest");
}

public void 
init()
{
    ::init();
    add_action(drink_water, "drink");
    add_action(water_animal, "water");
}
