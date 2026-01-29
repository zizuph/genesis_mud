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
    set_short("Hall of columns");
    set_long(BS("This is the south end of the immense hall. The hall extends " +
		"further to the north. The chamber echoes softly with the " +
		"sounds of any passage, quiet though it is. This is the " +
		"only room you have encountered so far that has survived " +
		"the Cataclysm without damage. This is due to the wonderful " +
		"dwarven construction - particularly the twenty-three " +
		"stately granite columns supporting the ceiling.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"column", "columns"}), BS("The columns are plain supports " +
		"with no ornate carvings or unusual shapes, but they seem " +
		"to have been constructed with great care. The fact that they " +
		"have survived the Cataclysm intact indicates that their " +
		"builders were accomplished engineers.", 70));

    add_exit(PSLA + "hall_col01", "north");

    add_prop(ROOM_I_LIGHT, 0);
}
