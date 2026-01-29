/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

public string door_open();

object gDoor;

void
create_pax_room()
{
    set_short("Fine carved tunnel");
    set_long("@@my_desc");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_exit(PSLA + "fine_tunnel05", "north");

    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid());

    gDoor = clone_object(POBJ + "d_fine_tunnel06");
    gDoor->move(TO);
}

public string 
door_open()
{
    if (gDoor->query_open())
	return "open";

    return "closed";
}


public string
my_desc()
{
    string desc;

    desc = "You are at the south end of the tunnel. Thick dust " +
		"covers the floor and the rubble. At the south wall is a " +
		door_open() + " door made of solid bronze. The tunnel " +
		"extends to the north where it seems to turn.\n";

    return desc;
}
