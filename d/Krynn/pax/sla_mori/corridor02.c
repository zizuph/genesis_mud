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
    set_short("Corridor");
    set_long("You are standing in a narrow corridor that runs from east " + 
	"to west. Loose chunks of rock litter the floor. The corridor seems " +
	"to widen further to the west. The floor is covered by old dust.\n");

    add_item(({"rock", "rocks"}), "The loose chunks of rock litter the floor.\n");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and stones on the floor.\n");

    add_exit(PSLA + "corridor01", "east");
    add_exit(PSLA + "corridor03", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
