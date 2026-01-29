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
    set_long("The forest feels dark and the sense of " +
        "danger grows. Thick branches " +
        "block light from filtering through. Patches of fog " +
        "drift across the path and lend an eerie feeling to " +
        "the tall dark pine trees, which cast shadows all around you. " + 
        "There is a dense tangle of undergrowth to each side " +
        "of the path, where only the brave (or foolhardy) " +
        "would care to explore.\n");
    set_tell_time(120);
    add_tell("You feel someone staring at you.\n");
    add_tell("Somewhere in the distance a wolf howls.\n");
    add_tell("A dense cloud of fog drifts across the path.\n");
    add_tell("Suddenly you duck, as an arrow whizzes past your " +
        "head and lands in the bushes to your left.\n");
    add_item((({"fog", "patches"})),
        "Patches of pea-soup fog make visibility poor.\n");
    add_item((({"undergrowth", "tangled undergrowth"})),
        "Along both sides of the path a dense network of bushes " +
        "and briars prevents you from entering the forest.\n");
    add_item((({"forest", "old forest"})),
        "The old forest climbs the flank of the mountainside, " +
        "and tall dark trees here block out the light.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_7", "north");
    add_exit("south_path_9", "southeast");
}
