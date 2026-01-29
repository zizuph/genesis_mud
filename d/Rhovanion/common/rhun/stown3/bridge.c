
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"
#include "/d/Ravenloft/guild/liches/tomes/tomeskill.h"
create_room()
{
set_short("Bridge");
set_long(break_string("This is a high-arching bridge.  It is solidly"
	+" built of a lightly-colored wood, and stretched across the"
	+" rapidly-flowing River Carnen below.  This small town straddles"
	+" the river, connected only by this one bridge.  You may"
	+" follow the bridge onto the town's main street to the north"
	+" or south from here. A mark is carved into the wooden framework."
	+"\n",75));
	
	add_item("mark","Its a mark of a skeletal hand holding an eye in its palm. you notice that it radiate a faint purple glow....\n");

AE(RHUN+"stown3/south_road","south",0);
AE(RHUN+"stown3/mid_road","north",0);

add_prop(ROOM_I_LIGHT,1);

}


int
do_touch(string str)
{
        if(str != "mark")
    {
        write("Touch mark perhaps?\n");
        return 1;
    }
 
    if (this_player()->query_skill(SS_RECRUIT_RESEARCH) != 5)
    {
    	write("What ?\n");
    	return 1;
     }

     write("Suddently, You are drafted into the wall..\n");
     this_player()->move_living("M", "/d/Ravenloft/shrines/shrine4", 1);
     
     return 1;
}



void
init()
{
    ::init();
    add_action(do_touch, "touch");
}