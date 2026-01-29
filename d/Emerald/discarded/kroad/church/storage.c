#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <filter_funs.h>
#include <cmdparse.h>

object *items = ({});

object
config_shelf(string where)
{
    object shelf;

    shelf = clone_object(VAMP_OBJ_DIR + "shelf");
    shelf->set_wall(where);
    shelf->move(this_object(), 1);
    return shelf;
}

void create_vamp_room()
{
    set_short("Storage room");

    set_long("   A large storage area.  It appears that it " +
        "has been recently restored, the shelves cleaned and repaired.\n");

    /* Keep this around so that the searching routines don't have to be
     * moved
     */
    add_item(({ "shelf", "shelves" }), "Several sets of heavy, wooden " +
        "shelves are placed against the walls.\n");

    add_exit("under_church03", "north");

    setuid();
    seteuid(getuid());

    setuid();
    seteuid(getuid());
    items = map(({ "north", "east", "west", "south" }), config_shelf);
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
     
void init()
{
    ::init();
    add_action(list, "list");
}

/*
 * Too often I thoughtlessly update the room and cause the
 * contents to be lost.  This should prevent that.
 */
void
remove_object()
{
    if (sizeof(FILTER_DEAD(deep_inventory(this_object()) - items - ({ 0 }))))
    {
        throw("Cannot destruct while items are present.\n");
    }

    destruct();
}
