/* Pax Tharkas, inside Sla-Mori.
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
    set_short("East tunnel");
    set_long(BS("You standing in a dusty, rock-strewn tunnel. The tunnel " +
		"is wide enough to allow two people to walk beside " +
		"each other. In the dust you can make out some sort " +
		"of tracks. The tunnel extends further to the east " +
		"and west. To the west you can see a crossroad.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"track", "tracks"}), "The tracks is animal tracks" +
		", probably made by rats.\n");

    add_exit(PSLA + "e_tunnel02", "east");
    add_exit(PSLA + "crossroad", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
