/*
*
*  coded by Amelia 4/12/97
*  
*  includes herbsearch and room_tell.c so that
*  they can be used if add_herb_file and add_tell
*  are used. The herb room should be inheritable
*  using ::create_herb_room(); in the file
*  after create_room()
*
*/
inherit "/d/Earthsea/std/room.c";
#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/properties.h"

/* Herb Search */
inherit "/d/Earthsea/herbs/specials/hs.c";
inherit "/d/Earthsea/lib/room_tell.c";


int flag = random(4);

void
create_herb_room()
{

    ::create_earthsea_room();
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
    set_tell_time(80);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    ::reset_room();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
	start_room_tells();
}

int
query_clover_flag()
{
    return flag;
}
