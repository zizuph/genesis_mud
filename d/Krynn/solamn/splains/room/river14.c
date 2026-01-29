/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the plains");
    set_long(BS("There is a river blocking your path south. The river " +
		"flows lazily through the plains coming from your west " +
		"and then turning northeast. You are " +
		"still on the plains, and the grass is just as dry as everywhere " +
		"else, since the level of the river is just too low. Beyond the " +
		"river the plains continue, but you can't get across the river.",SL));

    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is south of you and flows from " +
	     "the west to the northeast.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item("river",({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");


    set_noshow_obvious(1);
    add_exit(ROOM + "river15","west",0,3);
    add_exit(ROOM + "river13","northeast",0,3);
    add_exit(ROOM + "plain35","north",0,3);

    set_auto_reset(TABLE);
    reset_room();
}



