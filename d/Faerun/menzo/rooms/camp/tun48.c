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

    set_long("You are standing inside a large cave. The air is a little thin " +
	     "and light from the opening in the cliff is starting to wane as you " +
		 "travel deeper into the tunnel system.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels","tunnel"}),
        "You see one tunnel opening before you.\n");
    
    add_item(({"walls","rock"}),
        "The cave walls are cool to the touch, you see them gleam slightly, " +
        "hinting to you there may be a source of moisture nearby.\n");
    
    
	add_exit(CAMP_DIR + "tun47","north"); 
	add_exit(CAMP_DIR + "tun49","northwest");
	add_exit(CAMP_DIR + "tun46","northeast");
}