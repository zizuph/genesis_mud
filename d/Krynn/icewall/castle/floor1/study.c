/****************************************/
/*    Study of Icewall Castle */
/*       Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

object puppy;

void
reset_icewall_room() 
{
    if (!puppy) 
      {
	  puppy = clone_object(ICE_CAST_M + "puppy");
	  puppy->move(this_object());
      }
}

void
create_icewall_room()
{
    set_short("Study");
    set_long("\nAs you look around the room you are overcome by the vast"
	     + " amounts of literature to be found here. Shelves and shelves"
	     + " of books cover each of the four walls and a great oak"
	     + " table sits in the middle of the room. A log fire on the"
	     + " south wall gives off a gentle glow which tints everything in"
	     + " the room a golden orange. Two windows let in a small amount"
	     + " of daylight and from the window you can see vast amounts"
	     + " of snow and ice.\n");
    
    add_item(({"shelves","shelf","books","book"}),
	     "Several hundred books sit grandly in the shelves covering\n"
	     + "each of the walls.\n");
    add_item("table",
	     "This huge oak table must measure about eight foot by five\n"
	     + "foot.\n");
    add_item(({"fire","logs","log"}),
	     "The logs crackle in the fire and give off a soft glow.\n");
    add_item(({"window","windows"}),
	     "From the windows you can see out into the courtyard.\n");
    
    add_exit(ICE_CAST1_R + "main_hall.c", "east");
    
    reset_icewall_room();
}
