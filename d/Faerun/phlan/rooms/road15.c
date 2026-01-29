/*  /d/Faerun/phlan/rooms/road15.c
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
    extraline = "This broad avenue leads north toward the docks and old"
                +" city and west through the commercial district. To"
                +" the northwest is a post office and a bank is to the"
                +" northeast. Directly east is the city blackmsith and"
                +" south is the public forge. A series of shops are"
                +" arrayed to the west. The flagstones of the road you"
                +" are traversing are well used but clean.";
    
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
        
    add_item(({"blacksmith", "city blacksmith"}),
        "There is no mistaking a blacksmith's shop. Black, sooty smoke rises"
        +" from a chimney while the sounds of hammering and an occasional"
        +" profanity escape from the open doorway to the east.\n");  
        
    add_item(({"forge", "public forge"}),
        "Not as busy as the blacksmith's shop but equally unmistakable"
        +" is the city forge. Black, sooty smoke rises"
        +" from a chimney and you can hear a hammer steadily working"
        +" a piece of metal on an anvil. The open doorway leads to the"
        +" south.\n");         

    add_item(({"chimney", "chimneys"}),
        "Oversized tin chimneys blackened with soot and capped by crude"
        +" tops to prevent anything from falling or flying down them, they"
        +" belch forth clouds of sooty black smoke.\n");
        
    add_item(({"smoke"}),
        "Clouds of black sooty smoke belch from the chimneys. If not for a"
        +" brisk breeze it could prove to be a problem.\n");       

    add_item(({"post", "post office"}),
        "The post office is whitewashed and clean. Occasionally a runner"
        +" darts out the door on a delivery errand.\n");            

    add_item(({"bank"}),
        "The bank is bustling with people regularly going in and out"
        +" to contuct business.\n"); 
        
    add_item(({"shops"}),
        "There are several businesses along this avenue. By far the"
        +" busiest is the pub.\n");  

    add_item(({"pub"}),
        "You can tell nothing of it from here other than it must be"
        +" popular judging by the traffic.\n"); 
        
/*
*    Sound effects
*
*/

    add_room_tell("Sounds of hammering come from the blacksmith.");  

    add_room_tell("The sound of hammer on metal rings from the forge.");  

    add_room_tell("A male voice from the blacksmith shouts a string of"
     +" profanities that would make a sailor blush.");       
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road14", "north");
    add_exit(ROOM_DIR + "phlanforge", "south");    
    add_exit(ROOM_DIR + "phlansmith", "east");    
    add_exit(ROOM_DIR + "road16", "west");     
}



void
reset_faerun_room()
{
    set_searched(0);
}