/*  /d/Faerun/neverwinter/rooms/n2.c
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
    extraline = "You stand under the southwestern gate of Neverwinter. "
        +"The scene is crowded, as soldiers try to funnel the new arrivals. "
        +"On the side of the smooth stone walls are benches, packed with "
        +"people from all walks of life. There are a few spots left on "
        +"the benches.";
    
    set_short("Under Neverwinter's southwestern gate");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"walls", "wall"}),
       "The walls are smooth and delicate in design to the touch.\n");
		
    add_item(({"crowd"}),
       "The crowd is dense and diverse, like a hazy fog.\n");

    add_item(({"bench", "benches"}),
       "The benches are made of an imported wood from the forest to th"
       +"e east of Neverwinter. They are adorned with luscious cushions, "
       +"and the benches are inlaid with gold engravings.\n");
		


    reset_faerun_room();
        
    add_exit(ROOM_DIR + "n1.c", "south");
    add_exit(ROOM_DIR + "n3.c", "north");
}


void
reset_faerun_room()
{
    set_searched(0);
}