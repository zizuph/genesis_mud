/*  /d/Faerun/phlan/rooms/road1.c
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
    extraline = "This broad avenue leads from the docks to the east"
                 +" to the city wall to the west, some ways away. To the"
                 +" south the harbour continues to jut inland while."
                 +" to the north you see the town hall. The white"
                 +" flagstones are well used but clean.";
    
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
        "The city docks provide access to shipping travelling across the"
        +" bay or to farther destinations.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. You can"
        +" see a guardhouse farther to the west.\n");
        
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The Moonsea extends westward inland in the Phlan harbour. The "
        +"waters are dark blue and smell fresh and clean.\n");

    add_item(({"hall", "town hall"}),
        "The town hall extends the entire length of the street. The only"
        +" entrance is farther to the west. It is constructed of sturdy"
        +" limestone with stained glass windows.\n");
        
    add_item(({"glass", "stained glass", "window", "stained glass window"}),
        "The intricate stained glass window depicts a scene from over a "
        +" century ago when an adventuring party cleared a mixed group of"
        +" orcs and kobolds from Kuto's Well.\n");
    
    add_item(({"entrance"}),
        "The entrance looks massive from here. You will need to get closer"
        +" in order to make out any additional detail.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road2", "west");
    add_exit(ROOM_DIR + "dock1", "east");    
}


void
reset_faerun_room()
{
    set_searched(0);
}