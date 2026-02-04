/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * cave2.c (at the beach)
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <language.h>

#define SKELETON   PORT_DIR + "obj/skeleton"
#define KEY_HOLDER LOD_DIR + "obj/key_holder"

#define KEY_FILE   LOD_DIR + "obj/dung_key"
#define KEY_CODES  ({13501, 13502, 13503, 13504, 13505, 13506, 13507})

int *keys;

public string *
query_object_list()
{
    return ({SKELETON, KEY_HOLDER});
}

public void
reset_room()
{
    ::reset_room();
        
    keys = KEY_CODES;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("In a cave");
    set_long("You are standing in a cave. There seems to be an " +
             "opening to the west.\n");
    
    add_exit(PORT_DIR + "beach/cave1", "west", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    
    reset_room();
}

public string
do_search(object searcher, string str)
{
    object key;
    int n = random(sizeof(keys));
    
    if (!keys[n] || !searcher || ENV(searcher) != TO)
        return "";
    
    seteuid(getuid());
    key = clone_object(KEY_FILE);
    key->set_key(keys[n]);
    key->move(TO);
    
    keys[n] = 0;
    
    tell_room(TO, QCTNAME(searcher) + " found something.\n", searcher);
    return "You found " + LANG_ADDART(key->short()) + "!\n";
}
