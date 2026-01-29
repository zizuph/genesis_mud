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
    extraline = "You are in a southern part of the easter alleys. To the "
       +"southeast is a large run-down building, clearly not having been "
       +"as maintained as the buildings running up and down the main "
       +"street. To the east leads a to an even thinner alley. One could "
       +"easily pass it by thinking it was just a space in between the "
       +"alley's old and rotted buildings. The alley here continues to "
       +"the northeast, where out of the corner of your eye you spot un"
       +"savory figures jump swiftly out of view.";
    
    set_short("Somewhere in the eastern alleys of Protector's Enclave");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"alley"}),
       "The alley is clearly worn down and treated as a place where "
       +"several ne'erdowells and hooligans conspire as to who might "
       +"be robbed come nightfall. Most merchants and nobles avoid the "
       +"alleys like the plague, hugging their coin purse close to "
       +"their bodies.\n");
    
    add_item(({"building"}),
       "The building is old and can be stated to be in a ruined state. "
       +"Vines grow up the side of the building, adding a splash of "
       +"color to the bleak and drab alleys. Above the building's "
       +"entrance is a sign, worn down just as much as the rest of the "
       +"building.\n");
	   
    add_item(({"space"}),
       "The space in between the old and rotted buildings is incredibly "
       +"dark. Looking closely into the darkness, one may see the "
       +"flash of a dagger, being drawn from it's sheath.\n");
	   
    
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "nae2.c", "northeast");
    add_exit(ROOM_DIR + "n3.c" , "west");
	add_exit(ROOM_DIR + "m_AG.c" , "southeast");
	add_exit(ROOM_DIR + "s_inel.c" , "east");
}


void
reset_faerun_room()
{
    set_searched(0);
}