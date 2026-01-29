/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

object gDoor;

void
create_pax_room()
{
    set_short("Hall of columns");
    set_long(BS("You are standing in an immense hall that extends " +
		"further south. The chamber echoes softly with the " +
		"sounds of any passage, quiet though it is. This is the " +
		"only room you have encounted so far that has survived " +
		"the Cataclysm without damage. This is due to the wonderful " +
		"dwarven construction - particularly the twenty-three " +
		"stately granite columns supporting the ceiling. To the west " +
		"is small exit leading into a tunnel.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"column", "columns"}), BS("The columns are plain supports " +
		"with no ornate carvings or unusual shapes, but they seem " +
		"to have been constructed with great care. The fact that they " +
		"have survived the Cataclysm intact indicates that their " +
		"builders were accomplished engineers.", 70));

    add_exit(PSLA + "hall_col02", "south");
    add_exit(PSLA + "fine_tunnel01", "west");     

    seteuid(getuid());

    gDoor = clone_object(POBJ + "d_hall_col01");
    gDoor->move(TO);
    gDoor->set_key(TOMB_KEY);

    add_prop(ROOM_I_LIGHT, 0);
}
