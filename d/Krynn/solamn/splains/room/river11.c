/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;


create_splains_room()
{
    set_short("On the plains");
    set_long(BS("There is a river blocking your path east, south and west. The river " +
		"flows lazily through the plains coming from the northwest of " +
		"you , flowing around your south and then turning northeast. " +
		"This is a loop of the river but you are " +
		"still on the plains, and the grass is just as dry as everywhere " +
		"else, since the level of the river is just too low. Beyond the " +
		"river the plains continue, but you can't get across the river.",SL));

    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"loop","river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is west, south and east of you and flows from " +
	     "west to south to east around you.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item("river",({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");

    set_noshow_obvious(1);
    add_exit(ROOM + "river12","northwest",0,3);
    add_exit(ROOM + "river10","northeast",0,3);
    add_exit(ROOM + "plain22","north",0,3);
}



