/*  /d/Faerun/neverwinter/rooms/crack.c
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

inherit BASE_NEWERW_INDOOR;


void
create_neverw_room()
{
    set_long("A thief's hideout.\n"
        +"The room you've entered has a low ceiling and it lit poorly "
		+"The only furniture in the room is a desk, a small lantern "
		+"magically fixed to the desk, and a locked box hidden in a "
		+"corner.\n");
    
    set_short("A thief's hideout");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"walls", "wall"}),
       "The walls of the hideout are old and covered in moss and mold. "
       +"The thief clearly has a fascination in grafitti, as the walls "
       +"are mostly covered in vibrant paintings.\n");

    add_item(({"lantern"}),
       "The lantern is low on oil, given its flickering flame. A small "
       +"box lies next to it, hidden in the lamps shadow.\n");
	   
    add_item(({"small box"}),
       "The box contains a small flask of oil, presumably for the "
       +"flickering lantern.\n");

    add_item(({"desk"}),
       "The desk is dimly lit by the flickering lantern set on the desk. "
       +"A few small purses sit on the desk, their ropes cut. These can "
       +" only be the thief's spoils.\n");
	   
    add_item(({"box"}),
       "You may be in a thief's hideout, but isn't there supposed to be "
       +"honor amongst you?\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "nae2.c", "enter_crack");
}


void
reset_faerun_room()
{
    set_searched(0);
}