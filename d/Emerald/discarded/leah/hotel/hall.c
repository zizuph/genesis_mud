inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
	set_short("hall");
	set_long("   You are in a long narrow hall.  There are stairs "+
		 "leading down to the main entrance of the hotel. There "+
		 "are three doors leading off into the bedroom suites. "+
		 "At the end of the hall is a large window that looks "+
		 "down at the city below.\n\n");
  
 
	add_item("staircase", "It is a normal staircase leading down.\n");
	add_item(({"doors", "door"}), "There are three doors. One leading "+
		 "north, south and west.\n");
	add_item("north door", "The northern door reads The Royal Suite.\n");
	add_item("south door", "The southern door reads The Anniversery Suite.\n");
	add_item("west door", "The western door reads The Lover's Suite.\n");
	add_item("window", "As you look out the window you can see the center "+
		 "of Leah.  You can see the road leading off to the Chapel.\n");
 
	add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(VILLAGE_DIR + "hotel/entrance", "down");
	add_exit(VILLAGE_DIR + "hotel/bed2", "west");
	add_exit(VILLAGE_DIR + "hotel/bed3", "north");
	add_exit(VILLAGE_DIR + "hotel/bed4", "south");
}
