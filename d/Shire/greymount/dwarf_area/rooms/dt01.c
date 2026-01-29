/*
**Dwarven Mining Settlement Connecting Room # 01
**Created by Leia
**April 02, 2006
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Shire/greymount/dwarf_area/rooms/cave_base.c";

#include "/d/Shire/private/shire_admin.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "../defs.h"

void long_desc()
{
	test_random_items();
	return "You find yourself in a long tunnel somewhere in the middle of the dwarven mining settlement in the Grey mountains. All around you, dwarves come and go with the hustle and bustle that mining creates. This tunnel continues to the east and to the north, as well as to the west, where a gem shop has been set up. " + descrip_var + "\n";
}

void
create_room()
{

    set_short("A Tunnel in the Dwarven Mining Settlement");
    set_long(&long_desc());
    add_item(({"tunnel", "tunnels"}),
        "The tunnel is very long and expertly carved into the mountain. It continues to the east and to the north from here.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    
    set_add_rtells();
    
    add_exit(DT02, "east");
    add_exit(DT04, "north");
    add_exit(GEM_SHOP, "west");
    
}

void
reset_room()
{
	remove_item(var);
	set_long(long_desc());
}