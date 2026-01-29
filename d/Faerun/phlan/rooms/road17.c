/*  /d/Faerun/phlan/rooms/road17.c
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
                +" The armour shop is to the south and a weapon shop"
                +" is southesst. More shops are arrayed to the west and"
                +" east. The pub is to the southwest. The park to the"
                +" north is surrounded by a tall hedge. The flagstones of"
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
        +" casual observation.\n");

    add_item(({"park"}),
        "A hedge surrounds a small garden of greenery in the middle of the city.\n");      

    add_item(({"post", "post office"}),
        "The post office is whitewashed and clean. Its open door stands north"
        +" of you. Occasionally a runner darts out the door on a delivery"
        +" errand.\n");            

    add_item(({"weapon shop"}),
        "The Cutting Edge is a fine weapon shop. The entrance to the well-kept"
        +" building stands to the south.\n");
        
    add_item(({"shop", "armour shop"}),
        "The Best Defense is an armour shop of some local repute. The entrance"
        +" to the grey-painted building stands to the south.\n");       
        
    add_item(({"shops"}),
        "There are several businesses along this avenue, both to the east and"
        +" and west.\n");  

    add_item(({"pub"}),
        "The pub is rollicking with happy customers. A bright red awning announces"
        +" the name, but you must be closer to read it.\n");
        
/*
*    Sound effects
*
*/

    add_room_tell("Two members of the city guard pass by. One mentions to the other"
     +" his satisfaction with the armour he bought at The Best Defense.");  

    add_room_tell("A slight breeze hints of fresh sea air.");     
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "phlanarmshop", "south");    
    add_exit(ROOM_DIR + "road16", "east");    
    add_exit(ROOM_DIR + "road18", "west");     
}



void
reset_faerun_room()
{
    set_searched(0);
}