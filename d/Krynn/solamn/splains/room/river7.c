/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the plains");
    set_long(BS("There is a river blocking your path north. The river " +
		"flows lazily through the plains coming from the west of " +
		"you and going northeast. Another river is east of you, coming " +
		"from the south and both rivers merge to the northeast. You are " +
		"still on the plains, and the grass is just as dry as everywhere " +
		"else, since the level or the river is just too low. Beyond the " +
		"river to the north the plains continue, but you can't get across " +
		"the river. Across the river to your east is a large keep with strong " +
		"fortifications.",SL));

    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river","rivers"}),
	     "There is a river north of you and one east of you.\n");
    add_item(({"north river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is north of you and flows from west to northeast.\n");
    add_item(({"east river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is east of you and flows from south to north.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item(({"in north river","north river"}),({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");
    add_cmd_item(({"in east river","east river"}),({"swim","enter"}),
		 "The wall of the keep on the other side of the river would prevent " +
		 "you from climbing ashore, so you decide not to do that.\n");
    add_cmd_item(({"in river","river"}),({"swim","enter"}),
		 "There is a north river and an east river, which one do you want to enter?\n");
    add_item(({"keep","walls","fortifications","vingaard keep","wall"}),
	     "This is the mighty Vingaard Keep. Strong fortifications prevent anyone " +
	     "and anything from entering - at least from this direction.\n");

    set_noshow_obvious(1);
    add_exit(ROOM + "river6","west",0,3);
    add_exit(ROOM + "road8","south",0,3);
}



