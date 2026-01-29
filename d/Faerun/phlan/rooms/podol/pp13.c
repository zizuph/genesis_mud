/*  /d/Faerun/phlan/rooms/pp13.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "/d/Faerun/phlan/rooms/defs.h"

inherit BASE_PHLAN_OUTDOOR;

/*
*   Making the basic room. 
*/

void
create_phlan_outdoor()
{
    extraline = "Podol Plaza is a field of short clipped, manicured grass."
                +" It is still green and resilient despite being trod by many"
                +" feet every year. Podol Street lies to the north, leading"
                +" from the city wall and gate in the east to Podol Bridge across"
                +" the Stojanow River to the west. Kuto's Well is directly"
                +" to the east. The market is visible farther to the west.";
    
    set_short("Podol Plaza");

/*
*   Decorations
*/    
        
    add_item(({"plaza", "podol plaza"}),
        "Podol Plaza is an open air market. Though mostly selling items for"
        +" the residents of town and the outlying areas, there are stalls"
        +" from traders farther away selling their goods.\n"); 

    add_item(({"grass", "short grass", "clipped grass", "manicured grass"}),
        "Healthy green and clipped short, the grass of the plaza is well"
        +" maintained by both the city and the local merchants.\n");

    add_item(({"city", "phlan"}),
        "The port city of Phlan, on the shores of the Moonsea, stands to"
        +" the east. You are in Podol Plaza.\n");

    add_item(({"street", "podol street"}),
        "The dirt street is wide enough for a wagon, but any pedestrians"
        +" would have to get out of its way.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. The"
        +" city gate is to the east.\n"); 
        
    add_item(({"gate"}),
        "The gate is big enough to let a large wagon pass through with"
        +" ease.\n");        

    add_item(({"bridge", "podol bridge"}),
        "Not even visible from here, the Podol bridge crosses the"
        +" Stojanow River far to the west.\n");       
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"well", "kuto's well"}),
        "The well is about eight feet in diameter with a wooden canopy protecting it"
        +" from overhead contaminants and any drawing water from rain or other"
        +" inclement weather. The stones comprising the well are about three feet"
        +" high to keep out debris or careless hobbits. For more detail you would"
        +" need to get closer.\n");
        
/*
*   Sound effects
*/

    add_room_tell("You hear a splash as someone drops a bucket down the well.");       


    reset_faerun_room();

    add_exit(PODOL_DIR + "pp2", "northeast");         
    add_exit(PODOL_DIR + "pp3", "north");    
    add_exit(PODOL_DIR + "pp4", "northwest"); 
    add_exit(PODOL_DIR + "kw", "east");     
    add_exit(PODOL_DIR + "pp14", "west"); 
    add_exit(PODOL_DIR + "pp20", "southeast");     
    add_exit(PODOL_DIR + "pp21", "south");
    add_exit(PODOL_DIR + "pp22", "southwest");    
    
}


void
reset_faerun_room()
{
    set_searched(0);
}