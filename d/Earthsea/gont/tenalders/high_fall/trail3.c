/*
 * coded by Amelia 12/25/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
 * Changed syntax on around == Amelia 7/26/98
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include <ss_types.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "trail.h"
#include "trap.h"

public void
create_forest_room()
{
    set_short("Dark trail");
    set_long("A dark trail. Tree branches arch overhead "+
        "blocking the light. A tangle of briars and thick undergrowth "+
        "make walking here difficult. There is a small hut of "+
        "sod not far ahead to the north. " + "@@see_path");
    add_item((({"hut", "small hut"})),
        "There is a small soot-blackened hut ahead, which " +
        "appears to be made from partially burned sod.\n");
    add_item((({"briars", "trail", "undergrowth", "thick undergrowth" })),
        "You have to watch where you step, else you might " +
        "get off the trail.\n");
    add_item((({"branches", "tree branches"})),
        "A dense network of pine branches overhead makes it dark " +
        "and gives a sinister feeling to this place.\n");
    add_item("trap", "@@see_trap");
    set_tell_time(160);
    add_tell("You hear an owl hooting mournfully.\n");
    add_tell("A thick cloud of fog obscures the trail for a moment.\n");
    add_tell("You feel like someone is looking at you.\n");
    add_tell("Off to the right you hear a twig snap!\n");
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    reset_room();
    add_exit("trap_room", "north", 0, 0, 1);
    add_exit("trail2", "south", "@@test_loc", 0, 1);
    set_around_room("/d/Earthsea/gont/tenalders/high_fall/trail4", "north");
}

public void
init()
{
    ::init();
    init_trap_room();
}
