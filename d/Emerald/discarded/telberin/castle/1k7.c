/*
 * 1k7.c
 * Sitting Room off of the Central Hall courtyard
 * Original re-work by Jasmine
 * Updated description and added door message by Alaron August 15, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
   set_short("Sitting room");
   set_long("   This is the sitting room where many people come to sit "+
	    "and entertain themselves while waiting to be granted audience "+
	    "with the King and Queen. There are several comfortable-looking "+
	    "benches arranged neatly against the walls to provide a nice "+
	    "view of the center of the courtyard through the west archway. "+
	    "A cart with several dishes and serving jugs sits polished "+
	    "and unused in the middle of the room. A narrow, tall arch "+
	    "leads through the north wall to the library. A closed, "+
	    "old wooden door leads east.\n\n");

   add_item( ({"benches", "comfortable benches", "comfortable-looking benches"}),
	    "These benches are arranged neatly against the walls of the "+
	    "sitting room to allow for an optimal view of the beauty and "+
	    "serenity of the central courtyard.\n");

   add_item( ({"cart", "dishes", "jugs", "serving jugs"}),
	    "This cart rests unused and finely polished in the center "+
	    "of the sitting room. It is probably a decoration and more "+
	    "practical serving sets are used when guest require "+
	    "drink or refreshment.\n");

   add_item( ({"arch", "narrow arch", "narrow tall arch", "tall arch",
	       "north wall", "library", "north"}),
	    "The narrow, tall arch leaves through the emerald green wall "+
	    "underneath the leaf trim and opens into a dimly lit, musty-"+
	    "smelling room filled with books. You guess it is the "+
	    "library. However, knowing the elven thirst for knowledge, "+
	    "this is probably only one library of many.\n");

   add_item( ({"east", "door", "wooden door", "closed wooden door"}),
	    "It is an old, wooden door that has probably been banged "+
	    "against or knocked into thousands of times. It looks "+
	    "to be in pretty bad shape. You wonder what could be "+
	    "behind such a ratty-looking door amid all of this beauty "+
	    "and splendor.\n");

   add_exit(CASTLE_DIR + "1k11","east", "@@through_door@@");
   add_exit(CASTLE_DIR + "1k8","north");
   add_exit(CASTLE_DIR + "1k9","west");
   
}

int
through_door()
{
    write("\nYou easily pull open the wooden door and step into the "+
	  "room behind ... the door shuts behind you pulled by "+
	  "springs on the hinges ...\n\n");
    say(QCTNAME(this_player())+" pulls open the wooden door and steps "+
	"into the room behind ... the door shuts behind "+
	this_player()->query_objective()+" pulled by springs on the "+
	"hinges.\n");

    return 0;
}

	  
