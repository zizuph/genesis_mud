/* Pax Tharkas, inside Sla-Mori.
 *
 * 950401 by Rastlin, who can't spell right!
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("North end of Hall of the Ancients");
    set_long(BS("You are at the north end of Hall of the Ancients. The " +
		"gigantic hall must once have been splendid, but now it has " +
		"fallen into such decay that its faded splendor seems pathetic " +
		"and horrible. Two rows of seven columns runs the length of the " +
		"hall, though some lie shattered on the floor. The west " +
		"stone wall is rent by a huge hole. The floor and the shattered " +
		"columns are covered by dust.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item("hole", BS("It is a huge hole in the stone wall. Looking through " +
		"the hole you can see a tunnel extending to the west.", 70));

    add_cmd_parse("[the] [huge] 'hole'", "enter", "@@do_enter");

    add_exit(PSLA + "hall02", "south");

    add_prop(ROOM_I_LIGHT, 0);
}

public int
do_enter()
{
    TO->set_dircmd("hole");
    this_player()->move_living("through the hole", PSLA + "e_tunnel04", 0);
    return 1;
}
