/*  /d/Faerun/phlan/rooms/podol/pp10.c
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
                +" the Stojanow River to the west. Stojanow gate crosses the river"
                +" to the northwest. Valjevo Castle lies north of the gate. Far"
                +" to the southwest is the Cadorna textile mill, while more directly"
                +" south is Mantor library. The back of a vibrantly hued tent,"
                +" part of the market, stands to the southeast.";
    
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
        
    add_item(({"bridge", "podol bridge"}),
        "The Podol bridge crosses the Stojanow River to the west, leading"
        +" to the Valhingen Graveyard and farmlands beyond.\n");   
        
    add_item(({"graveyard", "valhingen graveyard"}),
        "You can't see the graveyard from here but ghost stories from a century"
        +" ago raise the hackles at the base of your neck when you think of the name.\n");  

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n"); 
        
    add_item(({"gate", "stojanow gate"}),
        "A large gatehouse of sturdy granite. I has massive doors of"
        +" reinforced wood that are currently closed. You cannot see"
        +" beyond them. A tower rises above the gate on each side,"
        +" overlooking the approach. Valjevo Castle stands behind the gate.\n"); 

    add_item(({"castle", "valjevo castle"}),
        "The castle rises gleaming above its protective walls in the"
        +" distance to the north.\n");                  
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");
        
    add_item(({"tent", "hued tent", "vibrantly hued tent"}),
        "A silken tent of a vibrant blue hue. The scents of herbs, spices"
        +" and flowers emanate from within.\n");

    add_item(({"mill", "textile mill", "cadorna textile mill"}),
        "It is too far distant to see details. The building is very"
        +" squarely built, almost blocky, and is of a whitish-grey stone.\n");
        
    add_item(({"library", "mantor library"}),
        "Light reflects off many large windows in the walls of the"
        +" gracefully designed library.\n"); 

    add_item(({"windows"}),
        "Many large windows line the walls of the library, presumably for natural"
        +" lighting for the readers inside.\n");        
        
/*
*   Sound effects
*/

    add_room_tell("The pleasant smell of herbs perfumes the air.");       


    reset_faerun_room();

    add_exit(PODOL_DIR + "pps15", "northwest");         
    add_exit(PODOL_DIR + "pps14", "north");    
    add_exit(PODOL_DIR + "pps13", "northeast");
    add_exit(PODOL_DIR + "pp11", "west");  
    add_exit(PODOL_DIR + "pp9", "east");      
    add_exit(PODOL_DIR + "pp17", "southwest");  
    add_exit(PODOL_DIR + "pp16", "south");     
    
}


void
reset_faerun_room()
{
    set_searched(0);
}