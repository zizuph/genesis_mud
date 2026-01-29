/*  /d/Faerun/phlan/rooms/road13.c
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
    extraline = "This broad avenue leads south away from the docks and"
                +" into the more commercial areas of the city. To the west"
                +" you see the side wall of the Cracked Crown Inn. To the south"
                +"east is a busy bank while to the east is a very peculiar dock."
                +" The flagstones of the road you are traversing are well"
                +" used but clean.";
    
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

    add_item(({"peculiar dock", "drydock", "station", "drydock station"}),
        "This dock is peculiar in that the berth for the ship is out of"
        +" the water. It somewhat resembles a drydock station but does"
        +" not have the normal repair and refitting equipment.\n");        
        
    add_item(({"inn"}),
        "The colorful inn sounds active and inviting.\n");     

    add_item(({"bank"}),
        "The bank is bustling with people regularly going in and out"
        +" to contuct business.\n");  
        
/*
*   Sound effects
*
*/        

    add_room_tell("Bank customers hurry past on their business.");         

        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road12", "north");
    add_exit(ROOM_DIR + "road14", "south");    
}



void
reset_faerun_room()
{
    set_searched(0);
}