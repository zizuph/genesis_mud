/*  /d/Faerun/phlan/rooms/road19.c
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
    extraline = "This broad avenue leads back east through the commercial"
                +" district of the city. Many townspeople are seen going"
                +" in and out of the public board to the south. You notice"
                +" mostly adventuring types going to the adventurer's guild"
                +" to the west. The pub is to the southeast and more shops"
                +" are arrayed to the east. The hedge wall of the park"
                +" stands north of you. The flagstones of the road you"
                +" are using are well used but clean.";
    
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
        
    add_item(({"hedge", "bushes"}),
        "A five foot tall hedge of thick green bushes screens the park from"
        +" casual observation.\n");

    add_item(({"park"}),
        "A small garden of greenery in the middle of the city.\n");            
        
    add_item(({"shops"}),
        "There are several businesses along this avenue, both to the east and"
        +" and west.\n");  

    add_item(({"pub"}),
        "The pub is rollicking with happy customers. A bright red awning announces"
        +" the name, but you must be closer to read it.\n");
        
    add_item(({"board", "public board"}),
        "To the south you see the public board. Obviously you need to get closer"
        +" to read any of the posts.\n");  

    add_item(({"guild", "adventurer's guild"}),
        "To the west is the squat brick adventurer's guild. It is an essential"
        +" stop before you make your way into wilder lands.\n");          
        
/*
*    Sound effects
*
*/

    add_room_tell("The sounds of vigorous training come from the west.");  

    add_room_tell("A kaleidoscope of butterflies fly north into the park.");     
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "phlanboard", "south");    
    add_exit(ROOM_DIR + "road18", "east");    
    add_exit(ROOM_DIR + "phlanag", "west");       
}



void
reset_faerun_room()
{
    set_searched(0);
}