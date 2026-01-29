/*
* Clyptas August 2017
*
*/

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short ("A three way intersection.\n");

    set_long("You stand at an intersection in the tunnel system. There are " +
         "two wide columns carved out of the stone on each side of the " +
         "openings. The lichen is everywhere, and you see different things " +
         "slithering about in the darkness.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see four tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "The cave walls are cool to the touch, you see them gleam slightly, " +
        "hinting to you there may be a source of moisture nearby.\n");
        
    add_item(({"columns"}),
         "Two wide, tall columns reside on either side of the three tunnel " +
         "openings. The columns are smooth and polished. Sconces are " +
         "embedded in the stone, a stairway of light traveling up each " +
         "column.\n");
         
    add_item(({"sconces"}),
         "The sconces are lit, and are emitting the same dull red glow as " +
         "the lichen. Upon closer inspection you see that each sconce isn't " +
         "lit at all, but is filled with the lichen that is covering the " +
         "stone. A sort of natural system for concentrating the light.\n");
         
    add_item(({"lichen"}),
         "The lichen is red and bright as it glows from withing the sconces. " +
         "You also see clumps of it growing along the cavern walls. The " +
         "lichen seems to ripple and sway, even though there is no breeze.\n");
    
    
    add_exit(CAMP_DIR + "tunnel6","northwest");
    add_exit(CAMP_DIR + "tunnel8","northeast");  
    add_exit(CAMP_DIR + "tun50","southeast");   
}