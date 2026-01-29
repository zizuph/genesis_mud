inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
 
	set_short("Hotel entrance");
	set_long(   "You are inside the entrance of a rather new "+
		"looking hotel. Off to one side, there is a stairway, while "+
		"further in you can see a rather large desk.  There is a "+
		"bench running along the stairwell. Double doors lead back "+
		"to the streets of Leah, and to another room in the hotel.\n\n");

	add_item(({"stairway", "stairs"}), "It is a narrow stairway with "+
		"steep steps leading upwards.\n");
	add_item("desk", "The desk is neat and tidy.  There is a book laying "+
		"on the desk.\n");
	add_item("bench", "The bench is for those waiting to register for a room."+
		"No one is waiting right now.\n");
	add_item("doors", "Both sets of double doors are delicatly designed with "+
		"roses and babies breadth ingravings. \n"); 
 
	add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(VILLAGE_DIR + "hotel/hall", "up");
	add_exit(VILLAGE_DIR + "centre", "east");
	add_exit(VILLAGE_DIR + "hotel/kitchen", "west");
	add_exit(VILLAGE_DIR + "hotel/parlor", "north");
	add_exit(VILLAGE_DIR + "hotel/bed1", "south");

 
}