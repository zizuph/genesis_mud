/* Pax Tharkas, inside Sla-Mori, in a tunnel.
 *
 * 950331 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("Tunnel");
    set_long(BS("You are standing in a tunnel that is leading " +
		"north and south, the tunnel is obviously ancient, " +
		"but whether it is natural or not is impossible " +
		"to tell. To the south can you see a crossroad. " +
		"The floor is covered with a great deal of dust.", 70));

     add_item("dust", BS("The dust seems to be very, very old. " +
	      "It must have been here for quite some time.", 70));

     add_item("floor", "There is a lot of dust on the floor.\n");

     add_exit(PSLA + "tunnel01", "north");
     add_exit(PSLA + "crossroad", "south");

     add_prop(ROOM_I_LIGHT, 0);
}
