/*  /d/Faerun/phlan/rooms/road8.c
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
    extraline = "This broad avenue continues east and west. Far to the east"
                +" are the docks. To the north is an entrance to the church."
                +" To the south is the entrance to the city park. The city"
                +" wall can be seen to the west. The white flagstones"
                +" of the avenue are well used but clean.";
    
    set_short("A broad avenue");
    
        
    add_item(({"avenue", "street"}),
        "The avenue is wide enough for a two wagons to travel side by"
        +" side. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter.\n");

    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

    add_item(({"limestone", "blocks"}),
        "This sturdy white stone is produced in local quarries.\n");

    add_item(({"dock", "docks"}),
        "The city docks are to the east but are too far away to see.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n");         
        
    add_item(({"church", "structure"}),
        "This building is unusual. From a distance it looks like a hammer"
        +" standing upright on its handle. The first and second floors"
        +" are round, possibly ten feet in diameter while the top floor"
        +" caps it with a rectangle thirty feet across and ten wide. On"
        +" top, surmounting the whole structure, is a statue of a gleaming"
        +" silver balance.\n");

    add_item(({"balance", "fulcrum", "crossbar", "dish", "statue"}),
        "The gleaming silver statue shines in the sun. It is a pointed"
        +" fulcrum with a crossbar suspending a flat dish on each end.\n");
        
    add_item(({"hedge", "bushes"}),
        "A five foot tall hedge of thick green bushes screens the park from"
        +" casual observation. An entrance through the hedge is to the south.\n");

    add_item(({"park"}),
        "A hedge surrounds a small garden of greenery in the middle of the city."
        +" The entrance stands directly to the south.\n");    

    add_item(({"entrance", "arch"}),
        "The entrance through the hedge leading into the park is a large arch"
        +" of the same bushes as the hedge. It allows admittance to the park."
        +" The entrance stands directly to the south.\n");  

    add_item(({"garden"}),
        "The park seems to be a garden of some sort with all manner of plants"
        +" growing in an orderly and well maintained fashion. From here you can"
        +"not make out any details of what is growing.\n");     

/*
*   Sound effects
*/

    add_room_tell("You jump out of the way just in time to avoid a wagon coming"
        +" around the corner from the west.");         


    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road9", "east");
    add_exit(ROOM_DIR + "church1", "north");  
    add_exit(ROOM_DIR + "road7", "west"); 
    add_exit(ROOM_DIR + "park2", "south");     
    
}


void
reset_faerun_room()
{
    set_searched(0);
}