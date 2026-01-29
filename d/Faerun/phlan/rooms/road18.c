/*  /d/Faerun/phlan/rooms/road18.c
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
    extraline = "This broad avenue leads east and west through the"
                +" commercial district of the city. While there is no"
                +" wagon traffic here the pedestrians make up for it."
                +" The pub is to the south and a armour shop"
                +" is southesst. More shops are arrayed to the west and"
                +" east. The pub is directly south and the entrance"
                +" to the park is north of you. The flagstones of"
                +" the road you are travelling are well used but clean.";
    
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
        +" casual observation. An entrance through the hedge is to the south.\n");

    add_item(({"park"}),
        "A hedge surrounds a small garden of greenery in the middle of the city."
        +" The entrance stands directly to the south.\n");    

    add_item(({"entrance", "arch"}),
        "The entrance through the hedge leading into the park is a large arch"
        +" of the same bushes as the hedge. It allows admittance to the park."
        +" The arcj stands directly to the north.\n");  

    add_item(({"garden"}),
        "The park seems to be a garden of some sort with all manner of plants"
        +" growing in an orderly and well maintained fashion. From here you can"
        +"not make out any details of what is growing.\n");      
        
    add_item(({"armour shop"}),
        "The Best Defense is an armour shop of some local repute. The entrance"
        +" to the grey-painted building stands to the south.\n");        
        
    add_item(({"shops"}),
        "There are several businesses along this avenue, both to the east and"
        +" and west.\n");  

    add_item(({"pub"}),
        "The pub is rollicking with happy customers. A bright red awning announces"
        +" the name and proprietor.\n");
        
    add_item(({"awning", "red awning"}),
        "A bright red awning overhangs the door of the Bitter Blade Pub."
        +" Aldo the Wine-Seller is proudly proclaimed as owner and operator.\n");        
        
/*
*    Sound effects
*
*/

    add_room_tell("Drunken singing can be heard coming from the pub.");  

    add_room_tell("You hear a loud toast and clinking glasses from the south.");     
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "phlanpub", "south");    
    add_exit(ROOM_DIR + "road17", "east");    
    add_exit(ROOM_DIR + "road19", "west");   
    add_exit(ROOM_DIR + "park5", "north");    
}



void
reset_faerun_room()
{
    set_searched(0);
}