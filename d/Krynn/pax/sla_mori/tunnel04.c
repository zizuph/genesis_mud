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
    set_short("Winding tunnel");
    set_long("You are standing in a narrow winding tunnel. The tunnel " +
	"takes a slight turn here and continues west and southeast. A thick " +
	"layer of dust covers the floor.\n");

    add_item("dust", BS("The dust seems to be very, very old. " +
	"It must have been here for quite some time.", 70));

    add_item("floor", "There is a lot of dust on the floor.\n");

    add_exit(PSLA + "tunnel05", "southeast");
    add_exit(PSLA + "tunnel03", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
