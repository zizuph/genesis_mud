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

    set_long("You are standing inside a large cave that seems to be a " +
        "conjunction of sorts. Three tunnels branch off from the main " + 
        "cavern you are standing in.\n");
    
    add_item(({"ground","floor","dirt"}),
        "The ground you stand on is a combination of hard packed dirt and rock.\n");
   
    add_item(({"tunnels"}),
        "You see four tunnel openings looming in front of you.\n");
    
    add_item(({"walls","rock"}),
        "The cave walls are cool to the touch, you see them gleam slightly, " +
        "hinting to you there may be a source of moisture nearby.\n");
    
    
    add_exit(CAMP_DIR + "tun38","northwest");
	add_exit(CAMP_DIR + "tun41","southwest"); 
	add_exit(CAMP_DIR + "tun36","northeast");
}