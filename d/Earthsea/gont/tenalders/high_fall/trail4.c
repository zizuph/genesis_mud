/*
 * coded by Amelia 12/25/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include <ss_types.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "trail.h"
#include "trap.h"
#include "defs.h"

public void
create_forest_room()
{
    object door;

    set_short("Dark trail");
    set_long("A dark trail. Tree branches arch overhead " +
        "blocking the light. A tangle of briars and thick undergrowth " +
        "make walking here difficult. In the gloom it is " +
        "difficult to find the path. Just to the north you see " +
        "an old sod hut, camouflaged among the bushes. " +
        "@@see_path");
    add_item((({"hut", "old hut"})),
        "There is an old sod hut just to the north. Its walls " +
        "and roof are made of blocks of peat-blackened sod, which " +
        "is somewhat ramshackle, but none the less sturdy.\n");
    add_item("trap", "@@see_trap");
    add_item((({"briars", "trail", "undergrowth", "thick undergrowth" })),
        "You have to watch where you step, else you might " +
        "get off the trail.\n");
    add_item((({"branches", "tree branches"})),
        "A dense network of pine branches overhead makes it dark " +
        "and gives a sinister feeling to this place.\n");
    set_tell_time(160);
    add_tell("You hear an owl hooting mournfully.\n");
    add_tell("A thick cloud of fog obscures the trail for a moment.\n");
    add_tell("You feel like someone is looking at you.\n");
    add_tell("Off to the right you hear a twig snap!\n");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/hut_out");
    door->move(this_object());
    door->set_key(BRASS_KEY);
    set_up_herbs(select_herb_files(FOREST_HERBS),
        FOREST_LOCATIONS, 3);
    reset_room();
    add_exit("trap_room", "south", 0, 0, 1);
    set_around_room("/d/Earthsea/gont/tenalders/high_fall/trail3", "south");
}

public void
init()
{
    ::init();
    init_trap_room();
}
