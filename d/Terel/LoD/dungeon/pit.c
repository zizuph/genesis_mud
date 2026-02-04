/*
 * pit.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define KEY      (LOD_DIR + "obj/chain_key")

int has_key = 1;

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2"});
}

public void
reset_room()
{
    ::reset_room();
    
    if (!has_key && random(3) == 0)
        has_key = 1;
}

public void
create_room()
{
    ::create_room();

    set_short("bottom of pit");
    set_long("You are down in a pit. There is lots of debris here, " +
             "mostly broken bones. You feel uneasy. A dark tunnel " +
             "opens up to the southwest.\n");

    add_item("debris", "Mostly old bones, but you notice some " +
             "half-rotten body parts as well. You begin to wonder " +
             "if there is something else around here who devour " +
             "people like you, since a fall down the pit wouldn't " +
             "make as much damage...\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(DUNG_DIR + "tunnel1", "southwest", 0);

    reset_room();
}

public string
do_search(object searcher, string str)
{
    if (!has_key || str != "debris")
        return "";
        
    seteuid(getuid());
    clone_object(KEY)->move(TO);
    has_key = 0;
    
    tell_room(TO, QCTNAME(searcher) + " found something among the debris.\n",
              searcher);
    
    return "You found a key among the debris!\n";
}
