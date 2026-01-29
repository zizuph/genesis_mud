#include "/d/Emerald/common/guild/vamp/guild.h"

#include <tasks.h>

inherit VAMP_ROOM_DIR + "vamp_room";

void create_vamp_room()
{
    set_short("Private study");
    set_long("   This was apparently once a small, private study.  " +
        "The room has been cleaned " +
        "out quite thoroughly:  not a single book is on the shelf " +
        "and only a few scraps of paper can be found on the floor. " +
        "Only a desk and chair remain.\n");

    add_item("shelves", "The shelves reach up to the ceiling on the " +
        "east wall.  All of the books have been removed.\n");

    add_item(({ "scraps", "paper", "scraps of paper" }),
        "A few small scraps of paper are on the floor.  None have " +
        "enough writing on them to make anything of them.\n");

    add_item(({ "chair" }), "A comfortable leather chair.\n");

    add_item("desk", "A large oak desk.  It has been emptied " +
        "completely.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "search_desk");
    add_exit("library", "north");
}

string search_desk(object who, string str)
{
    if (str != "desk")
    {
        return "";
    }

    if ((this_player()->query_skill(SS_AWARENESS) > 80) &&
        (this_player()->resolve_task(TASK_FORMIDABLE,
        ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0))
    {
        return "On the underside of one of the desk's drawers " +
             "is glued a small piece of paper which has four numbers " +
             "scribbled on it: 3 5 2 1.\n";
    }

    return "";
}
