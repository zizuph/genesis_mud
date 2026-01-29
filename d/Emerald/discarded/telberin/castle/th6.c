/*
 * TH6.c
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
    set_long("   You are standing in the central area of the Elven "+
	     "Courtrooms. They are extremely well furnished with all "+
	     "of the comforts and amenities one could ask for. The walls "+
	     "are covered with beautiful paintings, and the ceiling "+
	     "is supported by columns which have a speckled pattern "+
	     "of emerald green and white marble with gold leaf around "+
	     "the base and capital. Off to your east, through an "+
	     "impassible maze of food tables and columns, you notice "+
	     "a huge gathering of people around the thrones.\n\n");
    
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

    add_item(({"people", "guards"}),
	     "They are all milling about a small area filled with elves "+
	     "dressed in formal, royal clothing and colours. Even the "+
	     "guards are wearing sashes of the royal colours.\n");

    add_item("columns",
	     "The columns are tall and impressive, their faces speckled "+
	     "with an emerald green and white combination.\n");

    add_item( ({"tables", "food tables"}),
	     "The tables arrayed throughout the entire area are covered "+
	     "with food from what looks like all corners of the world. "+
	     "You notice that all of the people visiting the King and Queen "+
	     "(including some who appear destitute) are being encouraged "+
	     "to eat their fill.\n");

    add_exit(CASTLE_DIR + "th3","north",0);

   
}
