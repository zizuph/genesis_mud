/*  /d/Faerun/phlan/rooms/road9.c
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


void
create_phlan_outdoor()
{
    extraline = "This broad avenue passes near the city park towards the"
                +" city wall to the west and the docks to the east. It"
                +" also branches north towards a large building."
                +" To the northwest you see a church. To the northeast"
                +" is a shop sitting on a pier. To the south you see a"
                +" hedge.The white flagstones are well used but clean. ";
    
    set_short("A broad avenue");
    
        
    add_item(({"avenue", "street"}),
        "The avenue is wide enough for a two wagons to travel side by"
        +" side. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter.\n");

    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

    add_item(({"limestone"}),
        "This sturdy white stone is produced in local quarries.\n");

    add_item(({"dock", "docks"}),
        "The city docks are to the east but are too far away to see.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n"); 

    add_item(({"building"}),
        "A prominent building constructed of sturdy limestone stands"
        +" at the northern edge of town.\n");
        
    add_item(({"hedge", "bushes"}),
        "A five foot tall hedge of thick green bushes screens the park from"
        +" casual observation.\n");

    add_item(({"park"}),
        "A small garden of greenery in the middle of the city.\n"); 
        
    add_item(({"shop"}),
        "The shop is freshly whitewashed and seems open for business."
        +" It appears to be a general store from here.\n");

    add_item(({"church", "structure"}),
        "This building is unusual. From a distance it looks like a hammer"
        +" standing upright on its handle. The first and second floors"
        +" are round, possibly ten feet in diameter while the top floor"
        +" caps it with a rectangle thirty feet across and ten wide. On"
        +" top, surmounting the whole structure, is a statue of a gleaming"
        +" silver balance.\n");

    add_item(({"balance", "fulcrum", "crossbar", "dish"}),
        "The gleaming silver statue shines in the sun. It is a pointed"
        +" fulcrum with a crossbar suspending a flat dish on each end.\n");

    add_item(({"pier"}),
        "The pier is thick and sturdy. Its dark planking is well maintained.\n");
        
    add_item(({"planks", "planking"}),
        "The planks are two feet wide and a foot thick of heavy treated lumber.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road11", "east");
    add_exit(ROOM_DIR + "road8", "west");
    add_exit(ROOM_DIR + "road10", "north");    
}



void
reset_faerun_room()
{
    set_searched(0);
}