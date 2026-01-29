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
    set_short("East-West corridor");
    set_long("You are standing in a corridor, it extends both to the east " +
	"and west. The corridor widens a bit to the west. The air is stale " +
	"and musty, loose boulders and stones litter the floor, but " +
	"apparently a wide path runs down the center of the corridor. The " +
	"floor and boulders is covered by dust.\n");

    add_item(({"boulders", "boulder"}), "The boulders looks quite heavy.\n");

    add_item(({"stone", "stones"}), "The stones litter the floor.\n");

    add_item("path", "This path is free of any speck of dust and stones.\n");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and stones on the floor.\n");

    add_exit(PSLA + "corridor02", "east");
    add_exit(PSLA + "corridor04", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
