/* Pax Tharkas, inside Sla-Mori.
 *
 * 950408 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("West tunnel");
    set_long(BS("You standing in a dusty, rock-strewn tunnel. The darkness " +
		"seems thicker, and the air grows colder. This is strange " +
		"because the temperature is supposed to stay constant in " +
		"caves. The sense of evil is growing. The tunnel " +
		"is wide enough to allow two people to walk beside " +
		"each other. The dust on the floor of the tunnel shows the " +
		"passage of many feet. The tunnel extends further to the west " +
		"and to the east you can make out a crossroad.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"track", "tracks"}), BS("The tracks in the dust have been  made " +
		"by a number of different types of creatures. Most of the " +
		"tracks seems to be humanoid, although it is impossible " +
		"to tell. Most of the animal tracks are those of small, " +
		"clawed creatures.", 70));

    add_exit(PSLA + "crossroad", "east");
    add_exit(PSLA + "w_tunnel02", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
