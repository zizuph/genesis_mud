/*  /d/Faerun/phlan/rooms/dock3.c
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
    extraline = "To the north is another dock. Beyond the harbour continues to jut"
                 +" inland while to the south you see Thorn Island, a rocky"
                 +" island dominated by Sokol Keep. This dock is unusual in that"
                 +" it looks like a drydock station, holding the ship out of the"
                 +" water with the ability to lower it when needed. Absent are"
                 +" the usual repair and refitting equipment you would expect."
                 +" You have heard rumors of spelljammer ships, capable of not"
                 +" only waterborne travel but flight as well. Perhaps this is"
                 +" where one docks.";
    
    set_short("The Faerun dock");
    
/*
*   Decorations
*/   
        
    add_item(({"avenue", "street"}),
        "The avenue is wide enough for a two wagons to travel side by"
        +" side. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter.\n");

    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");

    add_item(({"keep", "sokol keep"}),
        "Sokol Keep is a small fortification on a rocky island, Thorn Island,"
        +" just south of the city.\n");

    add_item(({"island", "rocky island", "thorn island"}),
        "Thorn Island is a small rocky island south of the city. A defensive"
        +" fortification is built on it to guard seaward access to the city.\n");   

    add_item(({"dock", "docks"}),
        "This dock is peculiar in that the berth for the ship is out of"
        +" the water. It somewhat resembles a drydock station but does"
        +" not have the normal repair and refitting equipment. One of the"
        +" mighty spelljamming ships docks here, swiftly carrying"
        +" passengers west across Faerun.\n");
        
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The Moonsea extends westward inland in the Phlan harbour. The"
        +" waters are dark blue and smell fresh and clean.\n");

    add_item(({"ship", "spelljammer", "spelljamming ship"}),
        "This particular spelljammer looks like a large frigate. No sails are"
        +" set on its three tall masts. The whole ship seems to hum with magic.\n");

    reset_faerun_room();
         
    add_exit(ROOM_DIR + "dock2", "north");      
}


void
reset_faerun_room()
{
    set_searched(0);
}