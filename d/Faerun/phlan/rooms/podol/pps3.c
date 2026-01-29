/*  /d/Faerun/phlan/rooms/pps3.c
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
                +" gate through the city wall back into the town itself and"
                +" to the west it extends eventually to the bridge over the"
                +" Stojanow River. To the north is the Kovel Bridge"
                +" linking the plaza to the wealthy district. To the west"
                +" you can see Kuto's Well and Podol Plaza.";
    
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

    add_item(({"city", "phlan"}),
        "The port city of Phlan, on the shores of the Moonsea, stands to"
        +" the east. You are in Podol Plaza.\n");

    add_item(({"rut", "ruts"}),
        "A constant flow of trade goods to and from the farmlands and other"
        +" destinations have dug ruts easily six inches deep and twice that"
        +" wide into the street about four and a half feet apart.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. The"
        +" city gate is to the east.\n"); 
        
    add_item(({"gate"}),
        "The gate is big enough to let a large wagon pass through with"
        +" ease. A portcullis secures the gate from unwanted entrance"
        +" or exit. On the other side you see the city of Phlan.\n");      
    
    add_item(({"portcullis"}),
        "The portcullis stands fifteen feet high and fifteen wide. It is"
        +" constructed of vertical iron bars, crosshatched with straps"
        +" of the same iron horizontally. You catch curious shimmers in"
        +" the material.\n");
        
    add_item(({"bars", "straps", "material"}),
        "The bars are two inces thick and a foot in between. The straps"
        +" are inch thick and square, crossing the bars at a ninety degree"
        +" angle. You catch curious shimmers in the material.\n");      
        
    add_item(({"bridge"}),
        "The Podol bridge crosses the Stojanow River far to the west and the"
        +" Kovel bridge crosses it to the northwest.\n");   

    add_item(({"podol bridge"}),
        "Not even visible from here, the Podol bridge crosses the"
        +" Stojanow River far to the west.\n");   

    add_item(({"kovel bridge"}),
        "The Kovel bridge connects Podol Plaza to the wealthy sections of"
        +" town. The bridge is grey rock and cement with decorative brass"
        +" lanterns posted on each end.\n");  

    add_item(({"lantern", "lanterns"}),
        "Brass lanterns are mounted at each corner of the bridge burning"
        +" with a magical flame that requires no oil.\n");         
        
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
        
    add_exit(PODOL_DIR + "pps2", "east");    
    add_exit(PODOL_DIR + "pps4", "west");    
    
}


void
reset_faerun_room()
{
    set_searched(0);
}