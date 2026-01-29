/*
 * rubble.c
 *
 * Used in wild/t1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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
    set_name("rubble");
    add_name("heap");
    set_adj("small");
    set_short("small heap of rubble");
    set_long("This is a small heap of rubble that effectivly blocks all " +
             "movement east. It looks like you could move it though.\n");

    add_prop(OBJ_I_NO_GET, "It's way too heavy.\n");
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 10000);
}

int
do_move(string s)
{
    NF("Move what?\n");
    if (!id(s))
        return 0;

    NF("You move it around a little. It's not very fun, though.\n");
    if (find_object(WILDDIR + "t1") != environment(TO))
        return 0;

    TP->catch_msg("You move the rubble to the east, and reveal a new passage.\n");

    set_long("This is a small heap of rubble.\n");

    say(QCTNAME(TP) + " pushes some rubble to the east.\n");

    move(WILDDIR + "dc1");
    tell_room(WILDDIR + "dc1",
              "Some rubble falls down from a hole in one of the walls.\n");

    return 1;
}

void
init()
{
    ::init();

    add_action(do_move, "move");
}
