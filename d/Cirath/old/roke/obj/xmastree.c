/*
 * xmastree.c
 *
 * Used in wild/monk_discuss.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_long("A very nice looking xmas tree. You can dance around it. " +
             "There is a golden star on top of it.\n");
    set_short("xmas tree");
    set_name("tree");
    set_adj(({"xmas", "evergreen"}));
    add_item("star", "It is very beautiful.\n");
    add_prop(OBJ_I_NO_GET, "You greedy little sucker!\n");
}

void
init()
{
    ::init();

    add_action("dance", "dance");
}

int
dance(string s)
{
    if (s != "around tree")
        return 0;

    say(QCTNAME(TP) + " dances around the xmas tree.\n");
    write("You dance around the xmas tree.\n");

    return 1;
}
