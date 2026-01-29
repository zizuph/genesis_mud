/*  /d/Faerun/phlan/rooms/road2.c
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
    extraline = "This broad avenue leads from the docks, a ways to the"
                 +" east, to the city wall to the west not far away. To the"
                 +" south the harbour ends at a commercial pier. Waves"
                 +" break on sand and rocks beneath the pilings, splashing"
                 +" a fine spray of tangy mist into the air. You see the"
                 +" rear windows of a shop on the pier facing the water."                 
                 +" To the north you see the entrance of the town hall."
                 +" The white flagstones are well used but clean.";
    
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
        "The city docks off in the distance provide access to shipping "
        +" travelling across the bay or to farther destinations.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. You can"
        +" see a guardhouse farther to the west.\n");
        
    add_item(({"guardhouse"}),
        "It is hard to tell from here but the square stone guardhouse "
        +"seems to overlook a gate in the city wall.\n");
        
    add_item(({"gate"}),
        "You can't make much out from here but it looks big enough to let"
        +" a large wagon pass through with ease.\n");
        
    add_item(({"harbour", "sea", "moonsea", "waters"}),
        "The harbour ends at the pier. To the east it opens to the "
        +"Moonsea. The waters are dark blue and smell fresh and clean.\n");

    add_item(({"hall", "town hall"}),
        "The town hall extends the entire length of the street. The entrance"
        +" is directly to the north. It is constructed of sturdy limestone.\n");
        
    add_item(({"entrance"}),
        "The entrance stands close to ten feet tall with heavy oaken doors. "
        +" The thick bronze handles look as if they could be chained and"
        +" locked if the need arose.\n");
    
    add_item(({"door", "doors", "handles", "hinges"}),
        "The doors are made of stout oak with well greased, thick iron"
        +" hinges. Bronze handles an inch and a half in diameter and twelve"
        +" inches tall could easily be secured with a chain and lock.\n");
           
    add_item(({"waves"}),
        "The gentle waves are a foot and a half high and shade towards"
        +" green as they break.\n");
        
    add_item(({"sand", "rocks"}),
        "The coarse yellowish sand under the pier is littered with colurful"
        +" rocks polished smooth by the action of the waves.\n");
        
    add_item(({"spray", "mist"}),
        "The fine spray of mist sparkles brightly and smells of fresh."
        +" and clean.\n");
           
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
        
/*
* Sound effects
*/

    add_room_tell("A messenger runs into the town hall and then quickly"
    +" runs off to his next destination."); 
        
    add_exit(ROOM_DIR + "road1", "east");
    add_exit(ROOM_DIR + "road3", "west");
    add_exit(ROOM_DIR + "ch1", "north");
}


void
reset_faerun_room()
{
    set_searched(0);
}