/*
 * coded by Amelia 4/12/97
 * includes herbsearch and room_tell so that
 * they can be used if add_herb_file and add_tell
 * are used. The herb room should be inheritable
 * using create_herb_room() in the file.
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/herbs/specials/hs";
inherit "/d/Earthsea/lib/room_tell";

#include <stdproperties.h>
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/properties.h"

private int flag = random(4);

public void create_herb_room() { }

public nomask void
create_earthsea_room()
{
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
    set_tell_time(80);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    create_herb_room();
    reset_room();
}

public int
query_clover_flag()
{
    return flag;
}
