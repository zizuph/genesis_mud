/* Pax Tharkas, inside Sla-Mori.
 *
 * 950401 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

object gDoor;

void
create_pax_room()
{
    set_short("South end of Hall of the Ancients");
    set_long("@@my_desc");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_exit(PSLA + "hall02", "north");

    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid());

    gDoor = clone_object(POBJ + "d_hall03");
    gDoor->move(TO);
}

public string
my_desc()
{
    string desc;

    desc = "You are at the south end of Hall of the Ancients. Two rows " +
	   "of seven columns runs the length of the " +
	   "hall, though some lie shattered on the floor. Parts of the " +
	   "southwest wall has caved in, evidence of the destructive force " +
	   "of the Cataclysm. On the south wall of the hall stands a huge ";

    if (gDoor->query_open())
	desc += "open";
    else
	desc += "closed";

    desc += " bronze door. The floor and the shattered columns are covered " +
	    "by dust.";

    return BS(desc, 70);
}
