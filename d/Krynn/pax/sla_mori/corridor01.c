/* Pax Tharkas, inside Sla-Mori.
 *
 * 950401 by Rastlin 
 *
 * Navarre Sep 1st 2006, fixed a closed, an open bug. was always "a close and a open"
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

    gDoor = clone_object(POBJ + "d_corridor01");
    gDoor->move(TO);

    set_short("East end of corridor");
    set_long("@@my_desc");

    add_item(({"rock", "rocks"}), "The loose chunks of rock litter the floor.\n");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and stones on the floor.\n");

    add_exit(PSLA + "corridor02", "west");

    add_prop(ROOM_I_LIGHT, 0);
}

public string
door_line()
{
    if (gDoor->query_open())
	return "an open";

    return "a closed";
}

public string
my_desc()
{
    string desc;

    desc = "You are standing at the east end of a narrow corridor " +
	"that extends further to the west. On the north side of the corridor " +
	"is " + door_line() + " bronze door. Loose chunks of rock litter " +
	"the floor. The floor and the rocks are covered with old dust.\n";

    return desc;
}
