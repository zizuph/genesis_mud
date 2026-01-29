/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a bend in the hallway, which continues to " +
	     "your southwest, and also to your northwest. A door has " +
	     "been set into the wall, leading south.\n");
    
    add_exit(TURNA,"southwest");
    add_exit(CAVERN + "pal3","northwest");
    add_exit(CAVERN + "a5","south","@@only_with_prop");

    DARK;

    add_item("door","It's a sturdy metal door set into the rock.\nThe door is closed.\n");
    add_cmd_item("door","open","The door appears locked.\n");
    add_item("lock","Hmm, strange. You cannot find a lock.\n");
    add_cmd_item(({"door","lock"}),({"unlock","lock","pick"}),
		 "Hmm, strange. You cannot find a lock.\n");
    add_cmd_item("door","close","The door is closed already.\n");
    add_cmd_item("door",({"bash","break"}),
		 "You hit the door with all your strength, but it proves too strong for you.\n");
}

int
only_with_prop()
{
    if ((TP->query_prop(THIEF_I_CAN_ENTER) | 2 | 8) == 15)
      {
	  write("You press on the door and surprisingly, it swings open.\n" +
		"You walk through and the door closes behind you.\n");
	  return 0;
      }
    write("The door won't open.\n");
    return 1;
}
