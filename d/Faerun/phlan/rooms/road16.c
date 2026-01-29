/*  /d/Faerun/phlan/rooms/road16.c
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
    extraline = "This broad avenue leads east and west through the"
                +" commercial district of the city. While there is no"
                +" wagon traffic here the pedestrians make up for it."
                +" The post office is to the north and a weapon shop"
                +" is directly south. More shops are arrayed to the west"
                +" while the blacksmith and forge lay to the east."
                +" The flagstones of the road you are travelling are well"
                +" used but clean.";
    
    set_short("A broad avenue");
    
        
    add_item(({"avenue", "street"}),
        "The avenue is wide enough for a two wagons to travel side by"
        +" side. It is paved in white flagstones.\n");

    add_item(({"stone", "stones", "flagstone", "flagstones", "ground"}),
        "The flagstones are of a local white limestone. It shows wear"
        +" from use but is free from dirt and litter. There seems to be"
        +" something glinting in a crack between two of the stones.\n");
        
/*
*    There will be a small gem in the searchable crack
*
*/

    add_item(({"crack"}),
        "A slightly wider crack than usual. Something seems to be sparkling"
        +" faintly within. Perhaps you should search there?\n");
        
    add_item(({"city"}),
        "You are in the port city of Phlan on the shores of the Moonsea.\n");        

    add_item(({"limestone"}),
        "This sturdy white stone is produced in local quarries.\n");     
        
    add_item(({"blacksmith", "forge"}),
        "The blacksmith and forge are both to the east. Black, sooty smoke rises"
        +" from their chimneys and sounds of hammering can occasionally"
        +" be heard.\n");        

    add_item(({"chimney", "chimneys"}),
        "Oversized tin chimneys blackened with soot and capped by crude"
        +" tops to prevent anything from falling or flying down them, they"
        +" belch forth clouds of sooty black smoke.\n");
        
    add_item(({"smoke"}),
        "Clouds of black sooty smoke belch from the chimneys. If not for a"
        +" brisk breeze it could prove to be a problem.\n");       

    add_item(({"post", "post office"}),
        "The post office is whitewashed and clean. Its open door stands north"
        +" of you. Occasionally a runner darts out the door on a delivery"
        +" errand.\n");            

    add_item(({"shop", "weapon shop"}),
        "The Cutting Edge is a fine weapon shop. The entrance to the well-kept"
        +" building stands to the south.\n");
        
    add_item(({"shops"}),
        "There are several businesses along this avenue. By far the"
        +" busiest is the pub.\n");  

    add_item(({"pub"}),
        "It is difficult to see much it from here other than a bright red"
        +" awning and a steady traffic of customers.\n");
        
/*
*    Sound effects
*
*/

    add_room_tell("A slightly inebriated patron from the pub stumbles by.");  

    add_room_tell("The distant sound of hammer on anvil catches your ear.");     
        
        
    reset_faerun_room();
        
    add_exit(ROOM_DIR + "phlanpost", "north");
    add_exit(ROOM_DIR + "phlanwepshop", "south");    
    add_exit(ROOM_DIR + "road15", "east");    
    add_exit(ROOM_DIR + "road17", "west");     
}



void
reset_faerun_room()
{
    set_searched(0);
}