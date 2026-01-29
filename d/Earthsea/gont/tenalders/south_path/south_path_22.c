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
    set_long("The trail winds through dense undergrowth and " +
        "around rocks. Low-hanging branches obstruct the view ahead. " +
        "Clouds of mist seem to rise out of the forest gloom and " +
        "drift across the trail.\n");
    add_item((({"mist", "clouds of mist"})),
        "As the path rises more steeply, patches of fog or grey mist " +
        "swirl out of the forest, obscuring your view.\n");
    add_item("gloom", "A sense of gloom and danger seems to " +
        "loom from out of the forest.\n");
    add_item("branches",
        "Tree branches hang low across the path, obscuring your view.\n");
    add_item((({"trail", "rough trail" })),
        "It looks as though this trail was made recently. Trees " +
        "have been cut down, as if for firewood, and some logs lay " +
        "on the ground.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The old forest towers around you, flanking the sides of the " +
        "steep mountain.\n");
    add_item((({"pine needles", "needles", "path", "rugged path",
        "tangled undergrowth", "undergrowth" })),
        "Dense forest undergrowth prevents your leaving the rugged " +
        "path, and pine needles crunch under your feet as you walk.\n");
    add_item("rocks", "The path winds around large rocks and " +
        "an occasional boulder, which are natural for this " +
        "rough mountainous terrain.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_21", "northwest");
    add_exit("south_path_23", "south");
}
