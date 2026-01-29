/*  /d/Faerun/phlan/rooms/dock1.c
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
                 +" docks and appears to go all the way to the city wall some"
                 +" ways away. To the south the harbour continues to jut"
                 +" inland while to the northwest you see the town hall."
                 +" This dock services the schooner that crosses the"
                 +" Moonsea to the city of Melvaunt at the edge of Thar.";
    
    set_short("The Melvaunt dock");

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

    add_item(({"limestone"}),
        "This sturdy white stone is produced in local quarries.\n");

    add_item(({"dock", "docks"}),
        "This dock is where the barque to Melvaunt boards. There are boxes"
        +" and crates stacked and ready to be loaded.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. You can"
        +" see a guardhouse farther to the west.\n");
        
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The Moonsea extends westward inland in the Phlan harbour. The"
        +" waters are dark blue and smell fresh and clean.\n");

    add_item(({"hall", "town hall"}),
        "The town hall extends the entire length of the street. The only"
        +" entrance is farther to the west. It is constructed of sturdy"
        +" limestone with stained glass windows.\n");
    
    add_item(({"entrance"}),
        "The entrance looks massive from here. You will need to get closer"
        +" in order to make out any additional detail.\n");
        
    add_item(({"boxes", "crates"}),
        "These boxes and crates are full of trade goods to go to Melvaunt."
        +" They consist mostly of processed foodstuffs such as flour and"
        +" cheeses and construction materials.\n");

    add_item(({"melvaunt"}),
        "While you can't really see the city far to the northeast across"
        +" the Moonsea, you have heard it is a dangerous frontier outpost.\n");

    add_item(({"thar"}),
        "You have heard it is a wild land on the northern shore of the"
        +" Moonsea inhabited by orcs and other humanoids.\n");

    add_item(({"schooner"}),
        "The schooner is two-masted with a topsail. It seems well suited for"
        +" fast travel with a light cargo.\n");   

/*
*   Sound effects
*/

    add_room_tell("A fresh offshore breaze blows in from the Moonsea.");     

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road1", "west");  
}


void
reset_faerun_room()
{
    set_searched(0);
}