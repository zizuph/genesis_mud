/* created by Aridor 04/19/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r31", "east","@@door");
    add_exit(THEIWAR + "r26", "south");
    
    DARK;

    add_item(({"door","steel door"}),
	     "It's a very strong steel door. You are certain you wouldn't " +
	     "stand a chance of breaking it. Otherwise, you can't see " +
	     "anything special about it, though.\n");
    add_cmd_item(({"door","steel door"}),"open","The door seems locked.\n");
    add_cmd_item(({"door","steel door"}),"close","The door is closed already.\n");
    add_cmd_item(({"door","steel door","lock"}),({"unlock","lock","pick"}),
		 "You cannot find a lock!\n");
    add_cmd_item(({"door","steel door"}),({"break","bash"}),
		 "You bash against the door with all your might, but the " +
		 "door won't budge.\n");
}


string
my_long()
{
    if (TP->query_race_name() == "dwarf")
      return "You are standing in a hallway leading south. There is " +
	"a door here leading off to the east, but the hallway itself " +
	"ends here.\nA steel door is leading east.\n";
    return "You are standing in a hallway leading south. There is " +
      "a door here leading off to the east, but the hallway itself " +
      "ends here.\nA steel door is leading east.\n";
}

int
door()
{
    write("The door is closed.\n");
    return 1;
}
