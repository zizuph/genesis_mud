/*
 * 1k11.c
 * Storage room in the castle.
 * There was an exit leading off into telberin somewhere, but 
 * I removed it since it didn't seem that a storage room would 
 * have an open door leading outside a castle.
 * - Alaron August 15,1996
 */

#include "default.h"

inherit CASTLE_ROOM; 

void
create_room()
{
   set_short("Storage room");
   set_long("   This storage room is filled with dust, cobwebs and "+
	    "the damp, musty smell of mildew and soot. It looks as though "+
	    "it hasn't been used in a very long time. There are "+
	    "old, broken down chairs and tables stacked along the "+
	    "walls, possibly reserves for when the sitting room "+
	    "got overcrowded. A pile of crates is stacked against the "+
	    "north wall, and there is a closed wooden door leading "+
	    "out to the west.\n\n");
 
   add_item( ({"chairs", "tables", "walls", "old chairs",
	       "broken down chairs", "old, broken down chairs"}),
	    "The old, broken down chairs lie in sad piles of "+
	    "cracked and dust-covered wood against the walls, "+
	    "obviously neglected and unused for years.\n");

   add_item( ({"crates", "pile of crates"}),
	    "It is a pile of old, rotting crates. You can't quite "+
	    "make out what they used to hold, but its obvious they "+
	    "are too old and worn out to hold anything now.\n");

   add_item( ({"door", "closed wooden door", "wooden door",
	       "closed door"}),
	    "It is an old, nearly broken door. It doesn't look "+
	    "like anyone has taken care of it in a long time.\n");

   // add_exit(TELBERIN_DIR + "c4", "east");

   add_exit(CASTLE_DIR + "1k7", "west","@@through_door@@");
}

int
through_door()
{
    tell_room(CASTLE_DIR+"1k7",
	      "The wooden door creaks open to allow "+QTNAME(this_player())+
	      " through and slams shut again.\n",this_player());
    write("\nYou step through the wooden door, wincing at it slams shut "+
	  "behind you, nearly hitting you ...\n\n");
    say(QCTNAME(this_player())+" steps through the wooden door and "+
	"heads out of the storage room.\n");
    
    return 0;
}
