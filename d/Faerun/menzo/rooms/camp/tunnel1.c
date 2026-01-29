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

    set_long("You are standing in a large cave. Two tunnels branch out from " +
         "here. They grow darker the deeper they snake into the ground. The " +
         "earth beneath your feet declines slightly, and with each step you " +
         "feel as if you are sinking deeper into the bowels of the earth.\n");
    
    add_item(({"ground","floor","dirt","earth"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see two tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "The cave walls are cool to the touch, and slightly damp, you see " +
        "them gleam slightly hinting to you there may be a source of " +
        "moisture nearby.\n");
    
    add_exit(CAMP_DIR + "hidden_trail2", "out");
    add_exit(CAMP_DIR + "tunnel2", "northeast");
    add_exit(CAMP_DIR + "tun56","southeast");
}