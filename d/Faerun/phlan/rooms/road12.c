/*  /d/Faerun/phlan/rooms/road12.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_OUTDOOR;


void
create_phlan_outdoor()
{
    extraline = "This broad avenue leads from the docks to the east deeper"
                +" into the city to the west and south. To the north the"
                +" harbour continues to jut inland. A boisterous inn stands"
                +" to the southwest. The flagstones are well used but clean.";
    
    set_short("A broad avenue");
    
        
    add_item(({"avenue", "street"}),
        "The avenue is wide enough for a two wagons to travel side by"
        +" side. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter.\n");

    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

    add_item(({"limestone"}),
        "This sturdy white stone is produced in local quarries.\n");
        
    add_item(({"dock", "docks"}),
        "The city docks provide access to shipping travelling across the"
        +" bay or to farther destinations.\n");        
        
    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n");         

    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The harbour ends at the pier. To the east it opens to the"
        +" Moonsea. The waters are dark blue and smell fresh and"
        +" clean.\n");

    add_item(({"inn"}),
        "The colorful inn looks active and inviting.\n");
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "dock2", "east");
    add_exit(ROOM_DIR + "road11", "west");
    add_exit(ROOM_DIR + "road13", "south");    
}



void
reset_faerun_room()
{
    set_searched(0);
}