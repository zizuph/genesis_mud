/*
 * pit.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#define DUNG_DIR (LOD_DIR + "dungeon/")

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2"});
}

public void
create_room()
{
    ::create_room();
    
    set_short("dark tunnel");
    set_long("You are down in a dark but straight tunnel.\n");

    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(DUNG_DIR + "stunnel", "south", -7);
    
    reset_room();
}
