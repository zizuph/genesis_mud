/* created by Aridor 12/16/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the plains");
    set_long(BS("There is a river blocking your path north and east. The river " +
		"flows out of a gorge in the Vingaard mountains not far to " +
		"your west and now flows lazily through the plains just north of " +
		"you and then turns south. You are " +
		"still on the plains, and the grass is just as dry as everywhere " +
		"else, since the level of the river is just too low. Beyond the " +
		"river the plains continue, but you can't get across the river.",SL));

    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river comes from a narrow gorge in the Vingaard mountains " +
	     "to your west.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item("river",({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");
    add_item(({"mountains"}),
	     "The Vingaard mountains are further west. From here they look very " +
	     "impressive and unclimbable. A narrow gorge can be seen west of here " +
	     "where the river is flowing through.\n");

    set_noshow_obvious(1);
    add_exit(ROOM + "river2","south",0,3);
    add_exit(ROOM + "mount3","west",0,3);
}



