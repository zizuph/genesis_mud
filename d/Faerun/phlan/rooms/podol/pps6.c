/*  /d/Faerun/phlan/rooms/pps6.c
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
                +" old city, the town of Phlan itself. To the west Podol Street"
                +" skirts the plaza and eventually arrives at the bridge over the"
                +" Stojanow River. To the north, across the river, lies the wealthy"
                +" disctrict. Kuto's Well is to the southeast and Podol Plaza is"
                +" farther west and south.";
    
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
        
    add_item(({"bridge"}),
        "The Podol bridge crosses the Stojanow River far to the west and the"
        +" Kovel bridge crosses it to the northeast.\n");   

    add_item(({"podol bridge"}),
        "Not even visible from here, the Podol bridge crosses the"
        +" Stojanow River far to the west.\n");   

    add_item(({"kovel bridge"}),
        "The Kovel Bridge connects Podol Plaza to the wealthy sections of"
        +" town. The bridge is grey rock and cement with decorative brass"
        +" lanterns posted on each end.\n");  

    add_item(({"lantern", "lanterns"}),
        "Brass lanterns are mounted at each corner of the bridge burning"
        +" with a magical flame that requires no oil.\n"); 

    add_item(({"district", "wealthy district"}),
        "The wealthy district, or Kovel mansions, lie north of the Stojanow River."
        +" They are encircled by their own section of the city wall.\n");          
        
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
             

    reset_faerun_room();
        
    add_exit(PODOL_DIR + "pps5", "east");    
    add_exit(PODOL_DIR + "pps7", "west");  
    add_exit(PODOL_DIR + "pp2", "southeast");   
    add_exit(PODOL_DIR + "pp3", "south");
    add_exit(PODOL_DIR + "pp4", "southwest");    
    
}


void
reset_faerun_room()
{
    set_searched(0);
}