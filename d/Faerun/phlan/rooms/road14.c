/*  /d/Faerun/phlan/rooms/road14.c
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
    extraline = "This broad avenue leads south away from the docks toward"
                +" the commercial district of the city. To the northwest"
                +" you see the rear wall of the Cracked Crown Inn and the"
                +" kitchen vents exiting the roof. To the east is a busy"
                +" and secure bank with barred windows. West is the side"
                +" wall of the post office. The flagstones of the road you"
                +" are traversing are well used but clean.";
    
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

    add_item(({"window", "windows"}),
        "There are two windows facing the street in the bank. They"
        +" both are secured with iron bars.\n");     

    add_item(({"bar", "bars", "barred window", "barred windows"}),
        "The black iron bars are firmly mounted to the window frames"
        +" preventing any unwarranted entrance. The bars are an inch"
        +" thick with only three inches between them.\n");       
        
    add_item(({"inn"}),
        "The back wall of the inn is nondescript. You see several"
        +" exhaust vents exiting from the roof.\n");   
        
    add_item(({"post", "post office"}),
        "The side wall of the post office is whitewashed and clean.\n");       

    add_item(({"vent", "vents", "exhaust vent", "exhaust vents"}),
        "The exhaust vents are topped with a tin cap to prevent water"
        +" from getting into the kitchen as well as a meshwork to stop"
        +" any curious birds or squirrels from following the"
        +" delicious scents coming from within.\n");        

    add_item(({"bank"}),
        "The bank is bustling with people regularly going in and out"
        +" to contuct business. It stands directly to the east.\n");  
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road13", "north");
    add_exit(ROOM_DIR + "road15", "south");    
    add_exit(ROOM_DIR + "phlanbank", "east");    
}



void
reset_faerun_room()
{
    set_searched(0);
}