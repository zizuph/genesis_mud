/* Pax Tharkas, inside Sla-Mori.
 *
 * 950401 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

void
create_pax_room()
{
    set_short("End of east tunnel");
    set_long(BS("You standing at the end of a dusty, rock-strewn tunnel. " +
	"The tunnel extends further to the west. To the east is a " +
	"ancient stone wall rent by a huge hole through which only " +
	"darkness is visible. In the dust on the ground you can " +
	"see some tracks.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
      "on the floor.\n");

    add_item(({"track", "tracks"}), "These tracks are animal tracks" +
      ", probably made by rats.\n");

    add_item("hole", BS("It is a huge hole in the stone wall. Looking through " +
	"the hole you faintly can see the distant walls of a great " +
	"hall.", 70));

    add_cmd_parse("[the] [huge] 'hole'", "enter", "@@do_enter");

    add_exit(PSLA + "e_tunnel03", "west");

    add_prop(ROOM_I_LIGHT, 0);
}

public int
do_enter()
{
    set_dircmd("hole");
    this_player()->move_living("through the hole", PSLA + "hall01", 0);
    return 1;
}
