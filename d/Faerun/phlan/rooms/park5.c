/*  /d/Faerun/phlan/rooms/park5.c
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
    extraline = "This park is a garden oasis in the center of the city."
        +" It is surrounded by a hedge with an entrance directly to the"
        +" south. The garden is full of verdant flowers, plants, shrubs"
        +" and trees. It is tranquil and relaxing as the scents of herbs"
        +" and flowers surround you.";
    
    set_short("The city park");
    
/*
*   Making area able to be searched for herbs
*/    
    
    add_std_herbs("forest");    
        
    add_item(({"hedge", "bushes"}),
        "A five foot tall hedge of thick green bushes screens the park from"
        +" casual observation. An entrance through the hedge is to the south.\n");

     add_item(({"ground"}),
        "The ground is soft grass that does not retain footprints. It is soft"
        +" and springy.\n");
        
    add_item(({"entrance", "arch"}),
        "The entrance through the hedge leading out of the park is a large"
        +" arch of the same bushes as the hedge. It allows exit from the park."
        +" The entrance stands directly to the south.\n");         

     add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

     add_item(({"park", "garden", "oasis"}),
        "The park is a tranqul and relaxing escape from the city. It is"
        +" full of flowers, plants, shrubs and trees all in full bloom.\n");

    add_item(({"flower", "flowers"}),
        "Flowers in every color of the rainbow dot the garden and break"
        +" up the sea of green.\n");

    add_item(({"plant", "plants"}),
        "Many varieties of plants fill the park. Some are useful and"
        +" some are simply decorative. You could search for useful"
        +" ones as the garden is open to public use.\n");         
        
    add_item(({"shrub", "shrubs"}),
        "Waist high shrubs are artfully trimmed so they do not cause a"
        +" tangle or underbrush. They, like the rest of the park, are"
        +" well maintained.\n");

    add_item(({"tree", "trees"}),
        "Tall shade trees, some flowering and some not, stand here and there"
        +" throughout the garden dappling the park with shadows and rays"
        +" of broken sunlight.\n");
        
    add_item(({"shadows"}),
        "The shadows cast by the leaves of the trees look like organic works"
        +" of art as they move gently in the breeze.\n");

    add_item(({"scents", "smells"}),
        "Aromatic herbs, blooming flowers and vibrant plants fill the air with"
        +" the a complex dance of fragrances.\n");   
        


    reset_faerun_room();
        
    add_exit(ROOM_DIR + "park6", "east");
    add_exit(ROOM_DIR + "park2", "north");  
    add_exit(ROOM_DIR + "park4", "west"); 
    add_exit(ROOM_DIR + "road18", "south");   
    add_exit(ROOM_DIR + "park1", "northwest");
    add_exit(ROOM_DIR + "park3", "northeast");    
    
}


void
reset_faerun_room()
{
    set_searched(0);
}