/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

#include <macros.h>

void
create_splains_room()
{
    set_short("On the plains");
    set_long("There is a river blocking your path east and south. The river " +
	     "flows lazily through the plains coming from the northwest of " +
	     "you, flowing around your south and then turning north to " +
	     "your east. You are still on the plains, and the grass is just " +
	     "as dry as everywhere else, since the level of the river is " +
	     "just too low. Beyond the river you can see a road and some " +
	     "trees and bushes.\n");
    add_item(({"bridge"}),
	     "From here all you can see is that this is a stone bridge. " +
	     "There is something dark visible under the bridge from here, " +
	     "but you need to get closer to see anything specific.\n");
    add_item(({"trees","bushes"}),
	     "You can't see anything special from this distance.\n");
    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower " +
	     "than the plains. The river is south and east of you and flows " +
	     "from west to south to east around you. To your north you can " +
	     "see a bridge crossing the river.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "There is a bridge north from here if you want to go there.\n");
    add_cmd_item(({"into river","in river","river"}),({"swim","enter","jump"}),
		 "@@jump_into_the_river");

    set_noshow_obvious(1);
    add_exit(ROOM + "road8","north",0,3);
    add_exit(ROOM + "road7","northwest",0,3);
}



jump_into_the_river()
{
    write("You jump into the river.\n\n");
    TP->move_living("jumping into the river", ROOM + "under_bridge", 0, 1);
    write("You managed to pull yourself up on a narrow ledge on the east " +
	  "side of the river.\n");
    return "";
}
