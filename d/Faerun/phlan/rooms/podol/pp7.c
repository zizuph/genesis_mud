/*  /d/Faerun/phlan/rooms/pp7.c
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
                +" feet every year. Podol Street is immediately north leading"
                +" from the city wall and gate in the east to Podol Bridge across"
                +" the Stojanow River to the west. West of you is Podol Avenue,"
                +" leading into the plaza itself. A wooden railing prevents you from"
                +" entering from the sides. Kuto's Well is to the east. The back of"
                +" a colorful tent, part of the market, stands to the south.";
    
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
        "The dirt street is wide enough for a wagon, but any pedestrians"
        +" would have to get out of its way.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n"); 
        
    add_item(({"avenue", "podol avenue"}),
        "The avenue of cobblestones crosses the plaza from north to south.\n");  

    add_item(({"stones", "cobblestones"}),
        "The cobblestones are rounded smooth from traffic.\n");          
        
    add_item(({"bridge", "podol bridge"}),
        "The Podol bridge crosses the Stojanow River far to the west.\n");        
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");
        
    add_item(({"tent", "colorful tent"}),
        "A cloth tent with bright orange and white stripes. The armoma of"
        +" fresh cooked food assails your senses.\n");

    add_item(({"well", "kuto's well"}),
        "The well with its wooden canopy lies to the east.\n");
        
    add_item(({"railing", "wooden railing", "post", "posts"}),
        "The wooden railing is well smoothed and polised to prevent splinters."
        +" They are of red cedar between posts of the same material.\n");        
        
/*
*   Sound effects
*/

    add_room_tell("You hear a fresh sizzling as a piece of meat is put on the grill.");  
    add_room_tell("Fragrant wood smoke passes by.");   
    add_room_tell("Hungry customers travel along the avenue to the food market.");     


    reset_faerun_room();

    add_exit(PODOL_DIR + "pps9", "northeast");         
    add_exit(PODOL_DIR + "pps10", "north");    
    add_exit(PODOL_DIR + "pp6", "east");             
    
}


void
reset_faerun_room()
{
    set_searched(0);
}