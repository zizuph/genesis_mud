
/* entrance2.c
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "../goblins.h"

create_room()
{
    ::create_room();
    change_prop(ROOM_I_LIGHT, 1);
    change_prop(ROOM_I_INSIDE, 1);

    set_short("Just inside the goblin cave.");

    set_long(BSNN("You are just inside the goblin cave. " +
         "It is quite cool in here, and damp as well. " +
         "The musty odor of goblins comes from the north, " +
         "deeper in the cave, "+
         "while fresh air seems to come from the cave exit to the south. " +
         "You sense that you are being watched. "));

    add_exit(GOBLIN_CAVERN_DIR + "tunnel1", "north", 0, 0);
    add_exit(GOBLIN_CAVERN_DIR + "entrance1", "south", 0, 0);

    add_item(({"walls"}), BSN(
        "Looking closer, you see some small holes perforating the wall."));

}