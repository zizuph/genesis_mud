/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

object gWraith;

void
reset_pax_room()
{
    if (!gWraith)
    {
	gWraith = clone_object(PMONSTER + "wraith");
	gWraith->move(TO);
    }
}

void
create_pax_room()
{
    set_short("Chamber of Doom");
    set_long("The winding of the narrow tunnel finally ends in a dark " +
	"chamber. The air is heavy and cold here, and a nameless " +
	"sense of evil throbs somewhere within these slick, stony walls. " +
	"A thick layer of dust covers the floor, as if the frightened " +
	"creatures living in the tunnels knew better than to come here. " +
	"You are standing in a room known better as the Chamber of Doom. " +
	"The legend says that a graverobber broke into the Sla-Mori and " +
	"tried to plunder the tomb of Kith-Kanan. Forcing entrance " +
	"through the magic gate, he became trapped inside. Nourished only " +
	"by the force of his own evil, his mortal body perished and left only " +
	"the sinister presence that now dwells in this room.\n");

    add_item("dust", BS("The dust seems to be very, very old. " +
	"It must have been here for quite some time.", 70));

    add_item("floor", "There is a lot of dust on the floor.\n");

    add_exit(PSLA + "tunnel06", "north");

    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid());

    reset_pax_room();
}
