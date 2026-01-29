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
    
    set_short ("Inside a large dry cave.\n");

    set_long("The tunnel continues to decline, taking you deeper into the " +
        "darkness. The only light is the dull glow from the lichen growing " +
        "in condensed groups along the rock.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see four tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "The cave walls are cool to the touch, you see them gleam slightly, " +
        "hinting to you there may be a source of moisture nearby.\n");
    
    add_item(({"lichen","growth"}),
         "The red lichen is denser here. And the darker and deeper the " +
         "tunnels get the more it congregates. The lichen emits a dull " +
         "red glow.\n");
    
    add_exit(CAMP_DIR + "tunnel4","northwest");
    add_exit(CAMP_DIR + "tunnel6","southeast");   
}