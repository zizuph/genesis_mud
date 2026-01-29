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
    set_short("Tunnel branch");
    set_long(BS("You are standing at a branch in the tunnel. The air is colder " +
		"and the evil feeling flowing from the north tunnel is " +
		"strong. The tunnel also extends further to the east " +
		"and southwest. The dust on the floor shows the passage of " +
		"many feet. Loose chunks of rock litters the floor, and the " +
		"walls and ceiling are crumbling.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"track", "tracks"}), BS("The tracks is the dust is made " +
		"by a number of different types of creatures. Most of the " +
		"tracks seems to be humanoid, although it is impossible " +
		"to tell. Most of the animal tracks are those of small, " +
		"clawed creatures.", 70));

    add_exit(PSLA + "tunnel07", "north");
    add_exit(PSLA + "w_tunnel01", "east");
    add_exit(PSLA + "tunnel03", "southwest");

    add_prop(ROOM_I_LIGHT, 0);
}
