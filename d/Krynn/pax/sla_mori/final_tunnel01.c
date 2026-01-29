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
    seteuid(getuid());

    gDoor = clone_object(POBJ + "d_final_tunnel01");
    gDoor->move(TO);
    gDoor->set_key(FINAL_KEY);

    set_short("Fine carved tunnel");
    set_long("@@my_desc");

    add_item("dust", "Just plain dust, and a lot of it. There's a lot of " +
            "tracks in the dust. Probably rats.\n");

    add_item(({"rock", "rocks", "stone", "stones"}), "The chunks of rock " +
        "and the stones are littering the floor.\n");

    add_exit(PSLA + "final_tunnel02", "south");

    add_prop(ROOM_I_LIGHT, 0);
}

public string
door_line()
{
    if (gDoor->query_open())
	return "open";

    return "closed";
}

public string
my_desc()
{
    string desc;

    desc = "You are standing in a dark narrow fine carved tunnel. On the north " +
	"side of the tunnel is a " + door_line() + " wooden door. The tunnel " +
	"extends to the south. The floor is littered by loose chunks of " +
	"rock and stones. The floor is also covered by some old dust.\n";

    return desc;
}
