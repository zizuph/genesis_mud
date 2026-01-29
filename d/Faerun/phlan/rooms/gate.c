/*  /d/Faerun/phlan/rooms/gate.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_OUTDOOR;

/*
*   Making the basic room
*/

void
create_phlan_outdoor()
{
    extraline = "This gate is the only way through the ten foot thick wall"
                +" that surrounds Phlan. To the east is the city proper, while"
                +" to the west is Kuto's Well and the merchant district. A large"
                +" portcullis to the west can be used to secure the city. This"
                +" tunnel does not have lighting of its own, but is nonetheless"
                +" well lit from external sources.";
    
    set_short("Phlan city gate");

/*
*   Decorations
*/    
        
     add_item(({"avenue", "street"}),
        "The avenue is wide enough for a wagon to pass through the gate"
        +" with room to spare. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter.\n");

    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

    add_item(({"limestone", "blocks"}),
        "This sturdy white stone is produced in local quarries.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. The"
        +" guardhouse stands to the east.\n");
        
    add_item(({"guardhouse"}),
        "The guardhouse is impossible to see from inside the tunnel.\n"); 
        
    add_item(({"gate"}),
        "The gate is big enough to let a large wagon pass through with"
        +" ease. A portcullis secures the gate from unwanted entrance"
        +" or exit. On the other side you see a thriving marketplace"
        +" known as Kuto's Well.\n");
        
    add_item(({"marketplace", "well", "kuto's well"}),
        "The marketplace is colorful and busy. Kuto's Well is named after"
        +" the large well in the center of the plaza.\n");       
    
    add_item(({"portcullis"}),
        "The portcullis stands fifteen feet high and fifteen wide. It is"
        +" constructed of vertical iron bars, crosshatched with straps"
        +" of the same iron horizontally. You catch curious shimmers in"
        +" the material.\n");
        
    add_item(({"bars", "straps", "material"}),
        "The bars are two inces thick and a foot in between. The straps"
        +" are inch thick and square, crossing the bars at a ninety degree"
        +" angle. You catch curious shimmers in the material.\n");      
        
    add_item(({"shimmers"}),
        "The shimmers could be silver. If these bars are cold forged iron"
        +" with ingrained silver they could withstand seriously powerful"
        +" extra-planar entities.\n");          
        
    add_item(({"tunnel"}),
        "The tunnel is approximately fifteen feet high and traverses the"
        +" ten foot thick city wall. The city proper lies to the east,"
        +" while Kuto's Well and the marketplace are to the west.\n");


    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road6", "east");       
    
}


void
reset_faerun_room()
{
    set_searched(0);
}