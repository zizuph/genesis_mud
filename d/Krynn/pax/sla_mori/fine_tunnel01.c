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
    set_short("Fine carved tunnel");
    set_long(BS("You are at the north end of the tunnel. Thick dust " +
		"covers the floor and the rubble. To the east is a small " +
		"exit into a big hall. " +
		"The tunnel extends to the south into the darkness.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_exit(PSLA + "hall_col01", "east");
    add_exit(PSLA + "fine_tunnel02", "south");

    add_prop(ROOM_I_LIGHT, 0);
}
