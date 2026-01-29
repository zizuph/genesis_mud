/*  /d/Faerun/phlan/rooms/pps16.c
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
    extraline = "The bridge is of plain grey stone though of relatively newer"
                +" construction than many of the buildings in the area. It"
                +" crosses the western branch of the Stojanow River and"
                +" connects to Valhingen Road, which circles the Valhingen"
                +" Graveyard and passes through the farmland beyond. Stojanow"
                +" Gate is northeast overlooking the approach to Valjevo Castle"
                +" farther north of it. To the southwest you can see the Cadorna"
                +" Textile Mill and far to the south stands the Mantor Library."
                +" Kuto's Well and Podol Plaza are to the southeast along Podol"
                +" Road.";
    
    set_short("Podol Bridge");

/*
*   Decorations
*/    
        
    add_item(({"road", "street"}),
        "Both Podol and Valhingen Roads wide enough for a wagon, but any pedestrians"
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
        "The Podol bridge crosses the Stojanow River. It is of plain grey"
        +" stone and appears to be of relatively new construction. Previously"
        +" passage must have been by boat or barge.\n");   
        
    add_item(({"graveyard", "valhingen graveyard"}),
        "The graveyard is surrounded by a wrought iron fence. There is no"
        +" gate, only an open entrance with an iron arch across it bearing"
        +" the name VALHINGEN in block letters.\n");    

    add_item(({"fence", "arch"}),
        "The fence and arch are made of expertly crafted wrought iron.\n");  

    add_item(({"entrance"}),
        "Through the entrance you can make out shapes of tombstones and"
        +" mausoleaums, but can see no detail from here.\n");         
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the north, splitting to an eastern"
        +" and western branch, emptying into the Moonsea north of Phlan"
        +" and farther to the west, forming a large delta where the city"
        +" sits.\n");

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

    add_item(({"castle", "valjevo castle"}),
        "The castle rises gleaming above its protective walls in the"
        +" distance to the north.\n");  

    add_item(({"mill", "textile mill", "cadorna textile mill"}),
        "A large brick building with a minimal amount of windows.\n");     

    add_item(({"library", "mantor library"}),
        "Light reflects off many large windows in the walls of the"
        +" gracefully designed library.\n"); 

/*
*   Sound effects
*/

    add_room_tell("A fish jumps in the river with a loud splash.");    

    add_room_tell("Frogs croak along the banks of the river.");      
             

    reset_faerun_room();
           
    add_exit(PODOL_DIR + "pps17", "northwest"); 
    add_exit(PODOL_DIR + "pp15", "southeast");        
    
}


void
reset_faerun_room()
{
    set_searched(0);
}