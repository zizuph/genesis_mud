/*  /d/Faerun/neverwinter/rooms/1o.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_NEWERW_OUTDOOR;


void
create_neverw_outdoor()
{
    extraline = "You are in a southern part of the easter alleys. The "
       +"alley here continues to the north, where out of the corner "
       +"of your eye you spot unsavory individuals jump swiftly out "
       +"of view.";
    
    set_short("Somewhere in the eastern alleys of Protector's Enclave");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"individuals"}),
       "What you catch of the individuals before they slip from your "
       +"sight, are that they are all wearing black cloaks, with a "
       +"crimson trim. They seem to have disappeared behind a small "
       +"crack in one of the nearby buildings. A logo, depicting a "
       +"slashed coin purse is painted in black, almost invisible in "
       +"this light, to the right of the mysterious crack.\n");
		
    add_item(({"crack"}),
       "The crack is barely noticeable, and you only spot it because of "
       +"the shady individuals entering the crack to escape your gaze. "
       +"The crack is very small, and will only allow one person to "
       +"enter at a time. It's a wonder how the thieves were able to get "
       +"in so quickly.\n");
	   
    add_item(({"logo" , "coin purse" }),
       "The logo is barely noticible in the dark alley, no matter "
       +"what time of day it is. You discern that the group behind this "
       +"graffiti are the ones that make the common people so afraid of "
       +"Neverwinter's alleys.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "nae1.c", "southwest");
    add_exit(ROOM_DIR + "nae3.c", "north");
	add_exit(ROOM_DIR + "m_crack.c", "enter_crack");
}


void
reset_faerun_room()
{
    set_searched(0);
}