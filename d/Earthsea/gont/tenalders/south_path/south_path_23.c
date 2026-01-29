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
    set_long("Tall trees of the ancient evergreen forest " +
        "tower over you, scenting the crisp mountain air " +
        "with fresh pine. The forest floor is covered with dense " +
        "tangled undergrowth and rocks. A rugged path, carpeted with " +
        "pine needles, winds through the forest around the side of " +
        "the mountain. To the southwest the forest " +
        "thins.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The old forest towers around you, flanking the sides of the " +
        "steep mountain.\n");
    add_item((({"pine needles", "needles", "path", "rugged path",
        "tangled undergrowth", "undergrowth"})),
        "Dense forest undergrowth prevents your leaving the rugged " +
        "path, and pine needles crunch under your feet as you walk.\n");
    add_item("rocks", "Rocks and rubble fallen down from the " +
        "mountain make the path difficult to traverse.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_22", "north");
    add_exit("south_path_24", "southwest");
}
