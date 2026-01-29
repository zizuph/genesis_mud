/*
 * 3K2.c
 * This is the headquarters of the Keepers of Telberin
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
  set_short("Large foyer");
  set_long("   You are in a large, stone foyer. The usual glowing green "+
	   "stone which dominates most of the Telberin Castle is "+
	   "surprisingly absent here. The stone is gray and unyielding. "+
	   "Large stone columns fill the room at calculated, equal "+
	   "intervals, providing an interesting maze through which to "+
	   "wander. Three doors lead out of the sprawling chamber, each "+
	   "made of thick stone. The fourth door is a heavy wooden door "+
	   "leading south into the main foyer. You are drawn to the fact "+
	   "that throughout the entire chamber you hear not a single "+
	   "sound ... The entire area is filled with silence. The silence "+
	   "is a calming, peaceful silence, and not threatening.\n\n");

  add_prop(ROOM_I_INSIDE,1);

  add_item( ({"walls", "wall", "floor", "ceiling", "up", "down", "stone"}),
	   "The walls, floors and entire room is carved out of the same "+
	   "kind of gray, dull stone. The stone is cold and rough to the "+
	   "touch, very different from the smooth, warm, and softly "+
	   "glowing stone which fills the castle on the levels below. "+
	   "Stone columns fill the chamber at calculated, equal intervals. "+
	   "The columns, too, are made of this same stone.\n");

  add_item( ({"columns", "stone columns", "large stone columns", "column"}),
	   "The columns are extremely thick and made of dull, gray stone. "+
	   "Their undecorated surface is rough and cold to the touch.\n");

  add_item( ({"doors", "stone doors", "stone door", "three doors"}),
	   "The three stone doors lead off to the north, west, and east, "+
	   "each nestled between two of the stone columns, partially "+
	   "jutting out from the stone wall to form a half-column. The "+
	   "southern exit is a door made of incredibly thick wood, which is "+
	   "filled with knicks, dents and scrapes. It has obviously "+
	   "been in its share of battles.\n");

  add_exit(CASTLE_DIR + "3k5", "north");
 add_exit(CASTLE_DIR + "3k4", "west", "@@block_door@@");
  add_exit(CASTLE_DIR + "3k3", "east");
  add_exit(CASTLE_DIR + "3k1", "south");
}
	    
int
block_door()
{
    write("The door looks locked and securely fastened.\n");
    return 1;
}
