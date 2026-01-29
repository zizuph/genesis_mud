/**
* Coded by Louie 2004
* 
* Hatch (outer)
* Used in the Hatch Room (expl9.c)
*
*/
#pragma strict_types

#include "../local.h"

inherit "/std/door";

void
create_door()
{
	
    set_door_id("hatch");
    set_pass_command(({"u","up"}));
    set_door_name("hatch");
    set_open(0);
    set_other_room(GNOME_ROOM+"expl10");
    
}



