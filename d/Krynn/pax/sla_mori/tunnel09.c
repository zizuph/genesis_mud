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
    set_long("You are standing at a crossroad in the winding narrow tunnel. " +
	"The tunnel extends from east to west, but it also holds an opening to " +
	"south. Loose chunks of rock and a thick layer of dust covers the floor.\n");

    add_item(({"rock", "stone"}), "The loose chunks of rock and stones " +
	"litters the floor.\n");

    add_item("dust", BS("The dust seems to be very, very old. " +
	"It must have been here for quite some time.", 70));

    add_item("floor", "There is a lot of dust and stones on the floor.\n");

    add_exit(PSLA + "tunnel08", "east");
    add_exit(PSLA + "tunnel15", "south");
    add_exit(PSLA + "tunnel10", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
