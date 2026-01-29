/*  /d/Faerun/phlan/rooms/pps15.c
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
    extraline = "The road is of hard packed dirt. Far to the east is the"
                +" city of Phlan. To the northeast the Podol Bridge crosses"
                +" the western branch of the Stojanow River and leads to the"
                +" Valhingen Graveyard and the farmland beyond. Far to the"
                +" south you can see the Mantor Library. Cadorna Street leads"
                +" southwest towards the Cadorna Textile Mill. Across the river to"
                +" the northeast lies the Stojanow Gate and beyond that Valjevo"
                +" Castle. Kuto's Well and Podol Plaza are to the east.";
    
    set_short("Podol Street");

/*
*   Decorations
*/    
        
    add_item(({"road", "street"}),
        "The dirt street is wide enough for a wagon, but any pedestrians"
        +" would have to get out of its way. It is of hard packed dirt with"
        +" ruts from countless wagon wheels.\n");

    add_item(({"dirt", "packed dirt", "hard dirt", "hard packed dirt"}),
        "The brown dirt has been packed down hard by decades, if not centuries,"
        +" of feet, wagons and beasts of burden. Ruts from wagon wheels"
        +" are permanently sunk into the hard surface.\n");

    add_item(({"city", "phlan", "old city"}),
        "The port city of Phlan, on the shores of the Moonsea, stands to"
        +" the east. You are in Podol Plaza.\n");

    add_item(({"rut", "ruts"}),
        "A constant flow of trade goods to and from the farmlands and other"
        +" destinations have dug ruts easily six inches deep and twice that"
        +" wide into the street about four and a half feet apart.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n");     
        
    add_item(({"bridge", "podol bridge"}),
        "The Podol bridge crosses the Stojanow River to the nirthwest leading"
        +" to the Valhingen Graveyard and farmlands beyond. It is made of plain"
        +" unadorned grey stone.\n");   
        
    add_item(({"graveyard", "valhingen graveyard"}),
        "From here you can barely discern the wrought iron fence that surrounds"
        +" the graveyard and blocky shapes of what must be mausoleums. No"
        +" other details can be made out.\n");                 
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"well", "kuto's well"}),
        "Kuto's Well used to house dangerous humanoids, but is now one of"
        +" focal points of Phlan. It is the primary source of fresh water"
        +" for the residents of of the city as well as the areas south of"
        +" the Stojanow River.\n");
        
    add_item(({"plaza", "podol plaza"}),
        "Podol Plaza is an open air market. Though mostly selling items for"
        +" the residents of town and the outlying areas, there are stalls"
        +" from traders farther away selling their goods.\n"); 
        
    add_item(({"gate", "stojanow gate"}),
        "A large gatehouse of sturdy granite. I has massive doors of"
        +" reinforced wood that are currently closed. You cannot see"
        +" beyond them. A tower rises above the gate on each side,"
        +" overlooking the approach.\n");          
        
    add_item(({"tower", "towers"}),
        "The towers of Stojanow Gate rise up on each side of the entrance"
        +" itself. Soldiers can bee seen atop the towers manning the"
        +" defensive weapons.\n");   

    add_item(({"defensive weapons"}),
        "Though difficult to see from here you can make out a catapult and"
        +" several ballistae on each tower.\n");  

    add_item(({"catapult", "catapults"}),
        "You cannot make any details of these devices from here, just"
        +" that they are large and could fire deadly projectiles.\n");     

    add_item(({"ballista", "ballistae"}),
        "You cannot make out any details of these enormous crossbows"
        +" from here but the missiles they fire must be the size of spears.\n");          

    add_item(({"castle", "valjevo castle"}),
        "The castle rises gleaming above its protective walls in the"
        +" distance to the north.\n");  

    add_item(({"mill", "textile mill", "cadorna textile mill"}),
        "A large brick building with a minimal amount of windows.\n");     

    add_item(({"library", "mantor library"}),
        "Light reflects off many large windows in the walls of the"
        +" gracefully designed library.\n");           
             

    reset_faerun_room();
        
    add_exit(PODOL_DIR + "pps14", "east");    
    add_exit(PODOL_DIR + "pps16", "northwest"); 
    add_exit(PODOL_DIR + "pp10", "southeast");   
    add_exit(PODOL_DIR + "pp11", "south");     
    add_exit(PODOL_DIR + "cs1", "southwest");      
    
}


void
reset_faerun_room()
{
    set_searched(0);
}