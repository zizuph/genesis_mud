/* created by Aridor 12/20/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("At the foot of the mountains");
    set_long(BS("Impressive mountains rise up right to your west and northwest. " +
		"The plains stretch out to your east as far as you can see. " +
		"",SL));

    add_item(({"mountain","mountains","cliff"}),
	     "The mountains you see rise up direct in front of you to your west. " + 
	     "The mountain range runs in " +
	     "a southwest - northeastern direction. The cliff looks impossible to " +
	     "climb.\n");
    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the mountains.\n");
    add_cmd_item(({"mountain","cliff","mountains"}),"climb",
		 "You can't do that, it is just too steep.\n");


    set_noshow_obvious(1);
    add_exit(ROOM + "road1","northeast",0,3);
    add_exit(ROOM + "plain23","south",0,3);
    add_exit(ROOM + "plain4","east",0,3);
    add_exit(ROOM + "mount5","southwest",0,3);
}



