/*
 *  /d/Sparkle/area/anthive/rooms/room_std.c
 *
 *  The standardroom for the anthive.
 *
 *  Created November 2008, by Nerull.
 */

inherit "/std/room"; 

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int a = 0;


void
create_ant_hive()
{ 
		
}


	

int set_hive_level(int t)
{	 
	a = t;
	return a;
}

int query_hive_level()
{
	 return a;
}
	

void
create_room()
{
    create_ant_hive();
   
    add_prop(ROOM_I_INSIDE, 1);   
    add_prop(ROOM_I_LIGHT, 1);

    seteuid(getuid(this_object()));
}