/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

void
create_ld_room()
{
    set_short("In a hallway");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r19", "north");
    add_exit(THEIWAR + "r13", "east");
    add_exit(THEIWAR + "r12", "southeast");
    
    add_item(({"hallway","passageway"}),
	     "It's a hallway cut into the rock leading north and " +
	     "southeast. A small room lies to the east.\n");
    add_item(({"rock","wall","walls"}),
	     "It's hard rock!\n");
    add_item(({"cavern","chamber"}),
	     "The cavern to the north looks huge, but you can't " +
	     "see anything specific until you go there.\n");
    add_item(({"small room","room","east room","guard room"}),
	     "The room to the east looks like a guard room.\n");
    add_item(({"barrier","pole","wooden pole"}),
	     "A wooden pole which can be lowered, much like a " +
	     "frontier between countries.\n");
    add_cmd_item(({"barrier","pole","wooden pole"}),({"lower","raise"}),
		 "You lower the pole and raise it again. What fun.\n");

}


string
my_long()
{
    return "A passageway leading north and southeast. To the southeast, " +
      "the hallway leads downwards. In the north, you can make out the " +
      "hallway opening up into some huge chamber or cavern. Off to the " +
      "east from here you see a small room and some kind of barrier, " +
      "which can be lowered across the hallway." +
      "\n";
}
