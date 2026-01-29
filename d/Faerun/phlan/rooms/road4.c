/*  /d/Faerun/phlan/rooms/road4.c
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
    extraline = "This broad avenue passes near town hall towards the"
                +" city wall a short way to the west and the docks to the east."
                +" To the south you see a church. To the north you see the"
                +" town hall. In the distance you can hear waves gently washing"
                +" on the shore. The white flagstones you are traversing are"
                +" well used but clean.";
    
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
        "The city wall is carefully mortared and well maintained. You can"
        +" see a guardhouse farther to the west.\n");

    add_item(({"hall", "town hall"}),
        "The town hall extends the entire length of the street. The only"
        +" entrance is farther to the east. It is constructed of sturdy"
        +" limestone with stained glass windows.\n");
        
    add_item(({"entrance"}),
        "The entrance looks massive from here. You will need to get closer"
        +" in order to make out any additional detail.\n");
        
    add_item(({"glass", "stained glass", "window", "stained glass window"}),
        "The intricate stained glass window depicts a harrowing historical"
        +" scene. Almost a century ago the entire city was transported to"
        +" an enormous underground cavern by an insane Red Wizard of Thay."
        +" The original heroes of Phlan were able to foil the plan.\n");
        
    add_item(({"guardhouse"}),
        "The twenty food square stone guardhouse overlooks a gate in the"
        +" western city wall. It is two stories tall and looks large"
        +" enough to house several guards on each level.\n");
        
    add_item(({"gate"}),
        "The gate is big enough to let a large wagon pass through with"
        +" ease. A portcullis secures the gate from unwanted entrance"
        +" or exit.\n");
    
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
        
    add_item(({"church", "structure"}),
        "This building is unusual. From a distance it looks like a hammer"
        +" standing upright on its handle. The first and second floors"
        +" are round, possibly ten feet in diameter while the top floor"
        +" caps it with a rectangle thirty feet across and ten wide. On"
        +" top, surmounting the whole structure, is a statue of a gleaming"
        +" silver balance.\n");

    add_item(({"balance", "fulcrum", "crossbar", "dish", "statue"}),
        "The gleaming silver statue shines in the sun. It is a pointed"
        +" fulcrum with a crossbar suspending a flat dish on each end.\n");


    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road3", "east");
    add_exit(ROOM_DIR + "road5", "west");    
    add_exit(ROOM_DIR + "church1", "south");
    
}


void
reset_faerun_room()
{
    set_searched(0);
}