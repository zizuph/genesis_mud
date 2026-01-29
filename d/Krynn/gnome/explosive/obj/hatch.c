/**
* Coded by Louie 2004
* 
* Hatch (inner)
* Used in the Arming room (expl10.c)
*
*/
#pragma strict_types

#include "../local.h"

inherit "/std/door";

void
create_door()
{
	
    set_door_id("hatch");
    set_pass_command(({"d","down"}));
    set_door_name("hatch");
    set_open(0);
    set_other_room(GNOME_ROOM+"expl11");
    
}



