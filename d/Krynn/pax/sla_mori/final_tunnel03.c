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
    set_short("Dark tunnel");
    set_long("You are standing in a dark narrow fine carved tunnel that " +
	"leads both to the east and west. Loose chunks of rock and stones " +
	"litters the floor. The floor is also covered with a great deal of dust.\n");

    add_item(({"rock", "rocks", "stone", "stones"}), "The chunks of rock and the " +
	"stones is littering the floor.\n");

    add_item("dust", "Just plain dust, and a lot of it. There's a lot of " +
            "tracks in the dust. Probably rats.\n");

    add_exit(PSLA + "final_tunnel02", "east");
    add_exit(PSLA + "final_tunnel04", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
