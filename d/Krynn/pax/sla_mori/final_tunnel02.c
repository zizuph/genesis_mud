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
    set_long("You are standing in a dark narrow fine carved tunnel. The tunnel " +
	"takes a turn here, extending north and west. Loose chunks of rock and " +
	"stones is littering the floor. The floor and the stones is covered by " +
	"old dust.\n");

    add_item(({"rock", "rocks", "stone", "stones"}), "The chunks of rock and the " +
	"stones is littering the floor.\n");

    add_item("dust", "Just plain dust, and a lot of it. There's a lot of " +
            "tracks in the dust. Probably rats.\n");

    add_exit(PSLA + "final_tunnel01", "north");
    add_exit(PSLA + "final_tunnel03", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
