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
        "The dark forest looms to the west, and tall ancient evergreen " +
        "trees block your view in that direction. " +
        "The river flows very swiftly, carrying along chunks of ice " +
        "and rocks from higher elevations.\n");
    add_item((({"water", "whitewater", "whitewater river",
        "Ar", "river"})),
        "The river Ar rushes down the steep mountainside, its waters " +
        "cold, white, and frothy from melted snow.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The old forest towers to the west of you, ascending the " +
        "steep mountain.\n");
    add_tell("White swirling clouds of mist cross the path for " +
        "a moment.\n");
    set_tell_time(130);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_3", "north");
    add_exit("south_path_5", "southeast");
}

public void 
init()
{
    ::init();
    add_action(drink_water, "drink");
    add_action(water_animal, "water");
}
