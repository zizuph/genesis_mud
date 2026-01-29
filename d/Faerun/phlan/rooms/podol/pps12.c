/*  /d/Faerun/phlan/rooms/podol/pps12.c
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
    extraline = "The road is of hard packed dirt. To the east it leads to the"
                +" city of Phlan. To the west Podol Street continues along the"
                +" northern edge of Podol Plaza and eventually arrives at the"
                +" bridge crossing the Stojanow River. Across the river to the"
                +" north and northwest lie the Stojanow Gate and beyond that Valjevo"
                +" Castle. Kuto's Well is to the east and Podol Plaza is to the south.";
    
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
        "The Podol bridge crosses the Stojanow River far to the west leading"
        +" to the Valhingen Graveyard and farmlands beyond.\n");   
        
    add_item(({"graveyard", "valhingen graveyard"}),
        "You can't see the graveyard from here but ghost stories from a century"
        +" ago raise the hackles at the base of your neck when you think of the name.\n");                 
        
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
        +" from traders farther away selling their goods. You smell exotic"
        +" fruits and foodstuffs in the air.\n"); 
        
    add_item(({"gate", "stojanow gate"}),
        "A large gatehouse of sturdy granite. I has massive doors of"
        +" reinforced wood that are currently closed. You cannot see"
        +" beyond them. A tower rises above the gate on each side,"
        +" overlooking the approach.\n"); 

    add_item(({"castle", "valjevo castle"}),
        "The castle rises gleaming above its protective walls in the"
        +" distance to the north.\n");         
             

    reset_faerun_room();
        
    add_exit(PODOL_DIR + "pps11", "east");    
    add_exit(PODOL_DIR + "pps13", "west"); 
    add_exit(PODOL_DIR + "pp8", "south");    
    add_exit(PODOL_DIR + "pp9", "southwest");      
    
}


void
reset_faerun_room()
{
    set_searched(0);
}