/*  /d/Faerun/phlan/rooms/road11.c
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
    extraline = "This broad avenue travels east to the docks and west to"
                +" the city wall. To the north the harbour ends at a"
                +" commercial pier. Waves break on sand and rocks beneath"
                +" the pilings, splashing a fine spray of tangy mist into"
                +" the air. You see the rear window of a shop on the pier"
                +" facing the water. A boisterous inn stands to the south" 
                +" with a sign above the door. A hedge stands to the south"
                +" west. The flagstones are well used but clean.";
    
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
        
    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained.\n");         

    add_item(({"dock", "docks"}),
        "The city docks off in the distance provide access to shipping "
        +" travelling across the bay or to farther destinations.\n");

    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The harbour ends at the pier. To the east it opens to the "
        +"Moonsea. The waters are dark blue and smell faintly of"
        +" salt.\n");

    add_item(({"waves"}),
        "The gentle waves are a foot and a half high and shade towards"
        +" green as they break.\n");
        
    add_item(({"sand", "rocks"}),
        "The coarse yellowish sand under the pier is littered with colurful"
        +" rocks polished smooth by the action of the waves.\n");
        
    add_item(({"spray", "mist"}),
        "The fine spray of mist sparkles brightly and smells of salt.\n");
           
    add_item(({"pilings"}),
        "The tar-treated pilings supporting the pier are easily two feet thick."
        +" They appear aged but you know they will stand for decades.\n");
        
    add_item(({"pier"}),
        "The pier is thick and sturdy. Its dark planking is well maintained.\n");
        
    add_item(({"shop"}),
        "You can't see much from this angle but can tell by the fresh coat"
        +" of whitewash that the owner has pride in his business.\n");
        
    add_item(({"window", "windows"}),
        "The rear windows of the shop do not show anything of the interior.\n");
        
    add_item(({"hedge", "bushes"}),
        "A five foot tall hedge of thick green bushes screens the park from"
        +" casual observation.\n");

    add_item(({"park"}),
        "A small garden of greenery in the middle of the city.\n"); 

    add_item(({"inn"}),
        "The colorful inn looks active and inviting. The door is opened and"
        +" squarely mounted above it is a sign.\n");
        
    add_item(({"door"}),
        "The wooden door is open and welcoming.\n");       

    add_item(({"sign"}),
        "  ________________________\n"+
        " |                        |\n"+
        " |  T H E  C R A C K E D  |\n"+
        " |                        |\n"+
        " |        0  00  0        |\n"+
        " |        ||_|| /|        |\n"+
        " |        |   // |        |\n"+
        " |        --- ----        |\n"+
        " |                        |\n"+
        " |        C R O W N       |\n"+
        " --------------------------\n");
 

    add_room_tell("You hear occasional clinking of dishes and silverware"
    +" coming from the inn."); 
        

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road12", "east");
    add_exit(ROOM_DIR + "road9", "west");
    add_exit(ROOM_DIR + "inn", "south");    
}



void
reset_faerun_room()
{
    set_searched(0);
}