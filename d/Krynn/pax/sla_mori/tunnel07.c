/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("End of tunnel");
    set_long(BS("The tunnel you are standing in comes to an abrupt " +
		"end here. Crumbled stone and rubble is lying beneath " +
		"a hole in the west rock wall. The sense of malevolent " +
		"evil flowing from the darkness beyond the hole can " +
		"almost be felt, wafting across the flesh like a touch " +
		"of unseen fingers. The tunnel extends south into the " +
		"darkness.", 70));

    add_cmd_parse("[the] 'hole'", "enter", "@@do_enter");

    add_item("hole", "Looking through the hole you can see a narrow chamber.\n");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"stone", "rubble"}), "It must have fallen down from " +
	       "the walls and the ceiling.\n");

    add_exit(PSLA + "w_tunnel02", "south");

    add_prop(ROOM_I_LIGHT, 0);
}

public int
do_enter()
{
    set_dircmd("hole");
    TP->move_living("through the hole", PSLA + "tomb01", 0);
    return 1;
}
