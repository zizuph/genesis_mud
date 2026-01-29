// Garden gate 2a (/d/Avenir/common/bazaar/Obj/g_gate2a.c) 
// creator(s):   Tepisch Aug 94
// last update:  
// purpose:      To define the barriers of the garden

inherit "/std/door";
#include "/d/Avenir/common/bazaar/bazaar.h"

create_door()
{
    set_door_id("gate");
    set_pass_command(({"east","e","go east","out","enter","exit"}));
    set_door_name(({"gate","garden gate","wooden gate"}));
    set_door_desc("A chest-high wooden gate.\n");  
    set_other_room(EXTR + "str24");
    set_open(1);
    set_open_command(({"open","push","push open"})); 
    set_close_command(({"close","pull", "pull closed", "slam"}));
}             
