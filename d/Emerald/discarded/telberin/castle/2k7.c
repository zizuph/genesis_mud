/*
 * 2k7.c
 * Second Floor of Castle Telberin, Antechamber
 * - Alaron, September 12, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    
    set_short("Antechamber");
    set_long("@@room_desc@@");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"hangings","sculptures",
	   "hanging", "sculpture"}),
	     "The hangings and sculpture "+
	     "are all typically elven, light and delicate to the touch, yet "+
	     "something about them leads you to believe that there might "+
	     "be more than just artwork to these pieces.\n");

    add_item( ({"couches", "chairs", "cushioned chairs", "plush couches",
		"couch", "chair"}),
	     "The plush couches and cushioned chairs are set up neatly "+
	     "in the room to allow for easy conversation of those "+
	     "seated, while allowing them all a view of the "+
	     "entrance to the antechamber.\n");
    
    add_exit(CASTLE_DIR + "2k6","east",0);
    
}


string 
room_desc()
{
    return("   You are standing in some sort of antechamber. It is "+
	   "luxuriously decorated to instill a feeling of comfort "+
	   "and security. The plush couches and cushioned chairs rest "+
	   "in neatly arranged positions throughout the room. It looks like "+
	   "this is a place where nobility or priests would prepare "+
	   "themselves for ceremonies. The room is constructed of "+
	   "beautiful white marble with various hangings and sculptures "+
	   "around the room.\n\n");
}

