/*  /d/Faerun/phlan/rooms/dock2.c
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
*   Making the basic room. This will be the boat to Melvaunt.
*/

void
create_phlan_outdoor()
{
    extraline = "The broad avenue begins immediately to the west of the"
                 +" docks. To the north the harbour continues to jut"
                 +" inland while to the south you see a more peculiar dock."
                 +" This dock services the brigantine that crosses the"
                 +" Moonsea to the city of Mulmaster, nestled in the Earthspar"
                 +" Mountains.";
    
    set_short("The Mulmaster dock");
    
/*
*   Decorations
*/    
        
     dd_item(({"avenue", "street"}),
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
        "This dock is where the brigantine to Mulmaster boards. A more"
        +" peculiar dock is to the south. There are boxes and crates"
        +" stacked and ready to be loaded.\n");
        
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The Moonsea extends westward inland in the Phlan harbour. The"
        +" waters are dark blue and smell fresh and clean.\n");

    add_item(({"peculiar dock", "drydock", "station", "drydock station"}),
        "This dock is peculiar in that the berth for the ship is out of"
        +" the water. It somewhat resembles a drydock station but does"
        +" not have the normal repair and refitting equipment.\n");
        
    add_item(({"boxes", "crates"}),
        "These boxes and crates are full of trade goods to go to Mulmaster."
        +" You notice they contain a lot of military wares.\n");

    add_item(({"mulmaster"}),
        "While you can't really see the city far to the southeast across"
        +" the Moonsea, you have heard it has an evil reputation.\n");

    add_item(({"mountains", "earthspar mountians"}),
        "You have heard they are one of the larger mountain ranges"
        +" in the area and are very difficult to cross.\n");

    add_item(({"brigantine"}),
        "The brigantine is two-masted with a fully square-rigged foremast"
        +" and a gaff-sail mainsail and square topsail on the main mast. It"
        +" is larger and heavier than a normal inland sea schooner and looks"
        +" like it could have some fighting capacity.\n");
        
/*
*   Sound effects
*/

    add_room_tell("A fresh offshore breaze blows in from the Moonsea.");        

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road12", "west");  
    add_exit(ROOM_DIR + "dock3", "south");      
}


void
reset_faerun_room()
{
    set_searched(0);
}