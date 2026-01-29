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
    set_long("You are standing in a dark narrow fine carved tunnel that seems to " +
	"split up further to the west. The floor holds some debris " +
	"and very much dust. The tunnel extends to the east and west.\n");

    add_item("debris", "Looking closer at the debris you see, that it's " +
            "nothing more than leftovers of broken old useless boxes, " +
            "and pieces of rock, littered all over.\n");

    add_item("dust", "Just plain dust, and a lot of it. There's a lot of " +
            "tracks in the dust. Probably rats.\n");

    add_exit(PSLA + "final_tunnel03", "east");
    add_exit(LOW_LEVEL + "rubbles_entr", "west");

    add_prop(ROOM_I_LIGHT, 0);
}
