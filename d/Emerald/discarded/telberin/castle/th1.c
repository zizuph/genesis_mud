/*
 * Th1.c
 * Court Rooms area of Castle Telberin
 * - Alaron January 1997
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("The Telberin Courtrooms");
    set_long("   You are standing in the front area of the Elven "+
	     "Courtrooms. They are extremely well furnished with all "+
	     "of the comforts and amenities one could ask for. The walls "+
	     "are covered with beautiful paintings, and the ceiling "+
	     "is supported by columns which have a speckled pattern "+
	     "of emerald green and white marble with gold leaf around "+
	     "the base and capital. To the south you can see several "+
	     "people who look to be fairly important members of "+
	     "the Royal Court.\n\n");
    
    add_item( ({"comforts", "furnishings", "amenities"}),
	     "The comforts arrayed beautifully before you include soft-"+
	     "cushioned couches, golden-legged black marble tables decked "+
	     "out with exotic fruits, and much more. There are pictures "+
	     "and statues everywhere.\n");
    
    add_item("ceiling",
	     "The ceiling is an impressive sight, completely covered in "+
	     "intricate paintings.\n");
    
    add_item(({"paintings", "pictures"}),
	     "There are paintings and pictures everywhere. You don't "+
	     "really recognize any of the people in them, but you assume "+
	     "that they were either members of royalty or people related "+
	     "to them. A few of the paintings are depictions of various "+
	     "scenes important to Elven and Telberin history.\n");

    add_exit(CASTLE_DIR + "th2","west",0);
    add_exit(CASTLE_DIR + "th4","south",0);
    add_exit(CASTLE_DIR + "2k9","east",0);
   
}
