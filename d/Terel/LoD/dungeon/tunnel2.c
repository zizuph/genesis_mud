/*
 * tunnel.c
 *
 * A tunnel below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#define DUNG_DIR (LOD_DIR + "dungeon/")

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/bat2"});
}

public void
create_room()
{
    ::create_room();
    
    set_short("dark tunnel");
    set_long("You are down in a dark tunnel. There is lots of debris here, " +
             "mostly broken bones. You feel quite uneasy.\n");
             
    add_item("debris", "Mostly old bones, but you notice some " +
             "half-rotten body parts as well. You begin to wonder " +
             "if there is something around here who devour " +
             "people like you.\n");
             
    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(DUNG_DIR + "tunnel1", "northeast", -2);
    add_exit(DUNG_DIR + "cave", "east", 0);
    
    reset_room();
}
