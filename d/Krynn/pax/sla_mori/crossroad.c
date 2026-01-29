/* Pax Tharkas, inside Sla-Mori, at the crossroad.
 *
 * 950401 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("Crossroad");
    set_long(BS("You are at a crossroad. There is a tunnel " +
		"running east-west, and a tunnel leading north. The " +
		"floor is covered with a lot of dust. In the dust " +
		"you can make out some footprints in the east-west " +
		"tunnel but none leading north. A evil feeling " +
		"flows from the west tunnel.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"footprints", "footprint"}), BS("Strange, these are " +
		"tracks from human, " +
		"but they are not human, there is some animal tracks " +
		"as well, probably rats. What is odd, is that the animal " +
		"tracks end right here where the paths cross. They do " +
		"not go into the west tunnel. The other strange " +
		"tracks do not go into the east one.", 70));

    add_exit(PSLA + "tunnel02", "north");
    add_exit(PSLA + "e_tunnel01", "east");
    add_exit(PSLA + "w_tunnel01", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
