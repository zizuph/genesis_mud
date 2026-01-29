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
    set_long(BS("The tunnel you are standing in takes a turn " +
		"here and extends to the south and the west. Thick " +
		"dust covers the floor and the rubble.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_exit(PSLA + "fine_tunnel06", "south");
    add_exit(PSLA + "fine_tunnel04", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
