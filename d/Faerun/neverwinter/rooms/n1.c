/*  /d/Faerun/neverwinter/rooms/n1.c
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
    extraline = "You approach the ancient gates of Neverwinter. A small "
        +"but noticeable breeze pushes past you, making you shiver. "
        +"To the northwest and east you can see the outer walls of "
        +"Neverwinter, looking to the east, in the distance "
        +"you can see that the wall has "
        +"crumbled slightly. The gate itself towers "
        +"over you to the north, sending "
        +"a sense of both peril and grandeur. Travelers big and small "
        +"pass next to you, heading in or leaving the city.";
    
    set_short("Outside Neverwinter's South Gate");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"walls", "wall"}),
       "The walls that lead to the northwest are in prime "
       +"condition; however, in stark contrast, "
       +"the eastern wall seems to start crumbling after. "
       +"a certain point. Further off you think you "
       +"see that the wall has completely fallen apart.\n");
       
    add_item(({"crumbled wall"}),
       "The wall is disheveled and worn down. Scorch marks line "
       +"the top and bottom. You can make out a few figures atop it, "
       +"in which you can only assume "
       +"to be workers.\n");
	   
    add_item(({"gate"}),
       "The gate is made of solid stone, which is washed daily. "
       +"Depicted atop the gate is a bas relief of Mount "
       +"Hotenow erupting, "
       +"just as it did half a century ago.\n");
    
    add_item(({"travellers"}),
       "Most travellers you see seem to be fisherman, heading westward, "
       +"to Fisher's Float. "
       +"The other few seem to be adventurer's "
       +"such as yourself, or merchants, "
       +"grinning from cheek to cheek with the hopes of making "
       +"more coin than any one man should have.\n");
       
    add_item(({"road"}),
       "The road gradually changes from old to new. The newer "
       +"cobble has almost no wear to it, due to it being replaced "
       +"every week. The road also widens to allow for more foot traffic"
       +".\n");
	   
    add_item(({"fisher's float", "fishers float"}),
       "Across the sea, a little off the coast, is an earthmote. "
       +"From where you are, there is no discernable way to get on "
       +"the earthmote.\n");
	   
    add_item(({"bas relief"}),
       "Centered in the bas relief is a great erupting volcano; "
       +"however, rising from the erupting mass of land is a copy of "
       +"Neverwinter, as if saying it rose from the ashes.\n");
     
    add_item(({"figures"}),
       "From where you stand, the figures are hazy and you can't make "
       +"out anything other than the fact they seem to be working on "
       +"the wall.\n");
    
    add_item(({"city", "neverwinter"}),
       "The city's towers barely peek over the city's massive walls, "
       +"with the tallest belonging to the well-known libraries and "
       +"temples.\n");
	
    reset_faerun_room();
        
    add_exit("/d/Faerun/highroad/rooms/nrd13", "south");
    add_exit(ROOM_DIR + "n2.c", "north");
}


void
reset_faerun_room()
{
    set_searched(0);
}