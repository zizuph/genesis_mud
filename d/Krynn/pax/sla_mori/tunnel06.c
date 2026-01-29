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
    set_short("Winding tunnel");
    set_long("You are standing in a narrow winding tunnel that extends " +
	"north ans south, to the south the tunnel seems to come to an " +
	"end in a room. A thick layer of dust covers the floor.\n");

    add_item("dust", BS("The dust seems to be very, very old. " +
	"It must have been here for quite some time.", 70));

    add_item("floor", "There is a lot of dust on the floor.\n");

    add_exit(PSLA + "tunnel05", "north");
    add_exit(PSLA + "doom_chamber", "south");

    add_prop(ROOM_I_LIGHT, 0);
}
