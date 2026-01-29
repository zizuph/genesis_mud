/*  /d/Faerun/phlan/rooms/pp20.c
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
                +" feet every year. Kuto's Well is directly to the north while"
                +" Podol Street lies along the northern edge of the plaza."
                +" The city wall is to the south between the plaza and the shoreline."
                +" It is centuries old, but still well maintained and functional.";
    
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
        "Podol street lies along the northern edge of the plaza.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. On the"
        +" other side of the wall you can hear waves on the Moonsea"
        +" lapping against the shoreline.\n"); 
        
    add_item(({"gate"}),
        "The gate is big enough to let a large wagon pass through with"
        +" ease.\n");   

    add_item(({"gull", "gulls", "seagull", "seagulls"}),
        "White gulls with black tipped wings wheel in the sky, occasionally"
        +" diving out of sight behind the walls.\n");          
        
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

    add_room_tell("A flock of seagulls circle over the sea, far away.");                 

    reset_faerun_room();
 
    add_exit(PODOL_DIR + "pp12", "northeast"); 
    add_exit(PODOL_DIR + "kw", "north");    
    add_exit(PODOL_DIR + "pp13", "northwest");
    add_exit(PODOL_DIR + "pp19", "east"); 
    add_exit(PODOL_DIR + "pp21", "west");     
    
}


void
reset_faerun_room()
{
    set_searched(0);
}