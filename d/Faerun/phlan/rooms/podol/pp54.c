/*  /d/Faerun/phlan/rooms/pp54.c
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
                +" the plaza, where the city wall turns to the west. To the"
                +" west Podol Avenue crosses the market south to north."
                +" A nondescript tan tent is north at the corner of the market."
                +" The wall surrounding the plaza is to the east and south.";
    
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
        +" is the southern edge, while a short distance to the east"
        +" it turns north following the shoreline.\n");         

    add_item(({"bridge", "podol bridge"}),
        "Not even visible from here, the Podol bridge crosses the"
        +" Stojanow River far to the west.\n");       
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");
        
    add_item(({"trader's way"}),
        "Not visible from here, the road crosses the market from east to west,"
        +" and is crossed itself north and south by Podol Avenue.\n");           

    add_item(({"avenue", "podol avenue"}),
        "The road of cobblestones crosses the market from south to north,"
        +" and is crossed itself east and west by Trader's Way.\n");          

    add_item(({"tent", "plain tent", "tan tent", "nondescript tent"}),
        "A canvas tent of dark tan. It is rather plain and looks as if"
        +" it has not been used recently.\n");         
        
/*
*   Sound effects
*/

    add_room_tell("You notice the faint smell of fruit.");      


    reset_faerun_room();

    add_exit(PODOL_DIR + "pp46", "northeast"); 
    add_exit(PODOL_DIR + "pp53", "east"); 
    add_exit(PODOL_DIR + "pp55", "west");        
    
}


void
reset_faerun_room()
{
    set_searched(0);
}