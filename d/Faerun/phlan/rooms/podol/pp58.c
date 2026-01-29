/*  /d/Faerun/phlan/rooms/podol/pp58.c
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
                +" feet every year. You are at the southern edge of"
                +" the plaza, where the city wall runs east and south."
                +" A bright green tent stands to the north and a plain tan one"
                +" farther to the east. To the southwest you can see the Mantor"
                +" Library where the city wall again turns south following the"
                +" coastline.";
    
    set_short("Podol Plaza");

/*
*   Decorations
*/    
        
    add_item(({"plaza", "podol plaza", "market"}),
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
        "The busy street traverses the northern edge of the plaza.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. This"
        +" is the southern edge, with the wall turning yet south again"
        +" as it follows an outcropping of the shoreline.\n");         

    add_item(({"bridge", "podol bridge"}),
        "Not even visible from here, the Podol bridge crosses the"
        +" Stojanow River far to the west.\n");       
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");                 

    add_item(({"tent", "tents"}),
        "There is a bright green tent to the north and a plain tan tent"
        +" to the northeast.\n");          

    add_item(({"plain tent", "tan tent", "nondescript tent"}),
        "A canvas tent of dark tan. It is rather plain and looks as if"
        +" it has not been used recently.\n");  

    add_item(({"green tent", "bright green tent"}),
        "A cloth tent with bright green and white stripes. The armoma of"
        +" exotic fruits come strongly from within.\n"); 

    add_item(({"library", "mantor library"}),
        "Light reflects off many large windows in the walls of the"
        +" gracefully designed library. There are no doors visible on"
        +" the eastern side of the edifice.\n"); 

    add_item(({"windows"}),
        "Many large windows line the walls of the library, presumably for natural"
        +" lighting for the readers inside.\n");          
        
/*
*   Sound effects
*/

    add_room_tell("The smell of fresh fruit tantalizes your senses."); 
    add_room_tell("A glint of light catches your eye, reflected from the windows"
        +" of the library.");    


    reset_faerun_room();

    add_exit(PODOL_DIR + "pp47", "northwest"); 
    add_exit(PODOL_DIR + "pp57", "east"); 
    add_exit(PODOL_DIR + "pp59", "west");
    add_exit(PODOL_DIR + "pp68", "south");    
    
}


void
reset_faerun_room()
{
    set_searched(0);
}