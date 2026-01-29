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
    
    set_short ("In a tunnel system underground.\n");

    set_long("The cave grows darker the farther in you venture. You can hear " +
         "slight scuffling noises and the sound of water, still far off, but " +
         "present in the echoes.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see two tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "Placing your hand on the cool walls of the cave, you feel " +
        "a soft vibration in the stone.\n");
		
	add_item(({"light","glow"}),
	    "You see a dull red glow eminating from the tunnel in front of " +
		"you.\n");
    
    
    add_exit(CAMP_DIR + "tunnel4","east");
	add_exit(CAMP_DIR + "tunnel2","southwest");
}