/*
 * /d/Emerald/mist_tower/tower_storage.c
 *
 * A storage alcove in the tower which serves as the Vampire Guild.
 *
 * Copyright (c) ?? 1998 ?? by Shiva
 *
 * Revision History:
 *     10-3-00: (Gorboth) - Fleshed out room and item descriptions, as
 *                          well as attempting to make the interaction
 *                          with the three (basically) identical shelves
 *                          more intuitive for players
 *
 * Refactored to be the storage room in the crypt.
 * Louie 2007
 *
 */
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <cmdparse.h>
#include <filter_funs.h>

object *items;

object
config_shelf(string where)
{
    object shelf;

    shelf = clone_object(VAMP_OBJ_DIR + "shelf");
    shelf->set_position(where);
    shelf->set_no_show_composite(1);
    shelf->move(this_object(), 1);
    return shelf;
}

void
create_vamp_room()
{
    set_short("Storage room");
    set_long("A small alcove has been hewn from the rock, forming a "+
        "sort of storage space within the caves.  "+
        "Cobwebs and dust run heavily along the "+ 
        "stone, but three shelves look quite well used and "+ 
        "are mostly free of dust. They lie one each to the "+ 
        "right, left, and center.\n");

    add_item( ({ "shelves", "set of shelves" }),
        "There are three sets of shelves here. One on the right, one"
      + " in the center, and one on the left.\n");
    add_item( ({ "wall", "walls" }),
        "The walls here are angular and squared, having been crudely "+
        "carved simply to make a storage space. "+
        "They are covered in many places with "+
        "cobwebs and dust.\n");
    add_item( ({ "cobwebs", "web", "cobweb", "webs" }),
        "These cobwebs are thickly netted over large portions of the "+
        "wall. They lilt and stir slightly when movement disturbs the air.\n");
    add_item( ({ "dust" }),
        "The dust is very thick in many places of this room, especially"
      + " along the walls and corners of the floor. The three shelves"
      + " which hang along the wall are, however, mostly clear of it.\n");

    add_exit("crypt", "south");

    setuid();
    seteuid(getuid());
    items = map(({ "left", "center", "right", }), config_shelf);
}

int
list(string str)
{
    mixed *oblist;

    if (!strlen(str))
    {
        str = "all";
    }

    if (!parse_command(str, all_inventory(this_object()),
        "[the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!sizeof(filter(oblist, &->list_shelf_contents())))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    return 1;
}

public void
init()
{
    ::init();
    add_action(list,  "list");
}

/*
 * Too often I thoughtlessly update the room and cause the
 * contents to be lost.  This should prevent that.
 */
void
remove_object()
{
    if (sizeof(FILTER_DEAD(deep_inventory(this_object()) - items)))
    {
        throw("Cannot destruct while items are present.\n");
    }

    destruct();
}
