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
    
    set_short ("Inside a system of tunnels.\n");

    set_long("A large tunnel. The angle and curve of the stone have been " +
         "slightly manipulated, and you realize these tunnels are far from " +
         "natural.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see three tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "The walls are cool and damp to the touch. You see faint light " +
        "being emitted from some form of growth on the stone.\n");
        
    add_item(({"growth"}),
         "The red lichen on the cave walls grows sparsely here. Though the " +
         "darker and deeper the caves get the more it congregates. The " +
         "lichen emits a dull red glow.\n");
    
    
    add_exit(CAMP_DIR + "tunnel5","southeast");
    add_exit(CAMP_DIR + "tunnel14","northeast");
    add_exit(CAMP_DIR + "tunnel3","west");
}