
/* chamber.c
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "../goblins.h"

create_room()
{
    object door;

    ::create_room();
    change_prop(ROOM_I_LIGHT, 1);
    change_prop(ROOM_I_INSIDE, 1);

    set_short("Inside Sink hole.");

    set_long(BSNN("Here the cavern opens up somewhat into a small chamber. " +
        "A small sinkhole has formed here. " +
        "In order to secure the sinkhole, " +
        "the goblins have placed a grate over it."));

    add_exit(GOBLIN_CAVERN_DIR + "sinkhole", "up", 0, 0);

    add_item(({"hole", "sinkhole"}), 
        BSN("The sinkhole has formed because the ground underneath " + 
        "eroded until it collapsed. " +
        "There is probably some water down there!"));

    add_item(({"water"}), 
        "You cannot see any, but there must have been some once.\n");
    add_item(({"grate"}), "There is no way you could possibly open it\n");

    reset();

}
