inherit "/std/room";
#include "/w/stark/defs.h"
#include <macros.h>
void
 create_room()
 {
  ::create_room();
  set_short("Inside one of the large training tents");
  set_long("You stand inside a large training tent, protected from the wind and "
	  +"harsh gaze of the sun. Here, there are drinks and food for the trainees as "
	  +"they prepare themselves for their trials ahead. There are also bunks for "
	  +"resting during the hours of night and a few books on military strategy.\n");
  add_item(({"books","food","drinks","tent","room"}),
	  "These numerous foodstuffs, books, and drinks are scattered around the tent "
	 +"aimlessly. It would not be a wise idea to try and move anything, as it would "
	 +"anger the entirety of the camp.\n");
  
}

void
summon_ktrain()
{
    setuid();
    seteuid(getuid());
    
    object guard;
    
    guard = clone_object("/w/stark/celtcamp/ktrain.c");
    guard->move(this_object());
}
 