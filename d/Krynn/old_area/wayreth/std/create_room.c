/*
 *
 */
#pragma strict_types

#include "../local.h"
#include "/d/Krynn/common/defs.h"

inherit WAYINROOM;

static string gStudy = "blackstudy";
string gMy_long = "Test room\n";

public void
create_my_room() {}

nomask public void
create_wayreth_room()
{
    seteuid(getuid());

    create_my_room();

    restore_object(WLOG + "room/" + gStudy);
}

nomask static void
save_room()
{
    save_object(WLOG + "room/" + gStudy);
}

static int
do_items_remove(string str)
{
    return 1;
}

static int
do_items_add(string str)
{
    return 1;
}

static int
do_items_list(string str)
{
    return 1;
}

static int
do_change_short(string str)
{
    return 1;
}

public void
done_long_edit(string text)
{
    if (!text || !strlen(text))
	return;
    
    gMy_long = text;
    
    TP->command("$snap");

    tell_room(TO, "There is a bright flash and you can feel the ground " +
	      "shake.\n");
    save_room();
}

static int
do_change_long(string str)
{
    write("You are about to change the long description of the room.\n\n");
    clone_object("/std/edit")->edit("done_long_edit", gMy_long);
    return 1;
}

public void
init()
{
    add_action(do_items_remove, "itemsremove");
    add_action(do_items_list, "itemslist");
    add_action(do_items_add, "itemsadd");
    add_action(do_change_long, "changelong");
    add_action(do_change_short, "changeshort");
    ::init();
}



