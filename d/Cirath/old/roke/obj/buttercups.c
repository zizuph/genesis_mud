/*
 * buttercups.c
 *
 * Used in wild/r1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_short("yellow flower");
    set_adj("yellow");
    set_name("flower");
    add_name("buttercups");
    set_long("It is some buttercups.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);

}

void
init()
{
    ::init();

    add_action("smell", "smell");
}

int
smell(string s)
{
    notify_fail("Smell what?\n");
    if (s != "flower" && s != "flowers" && s != "buttercups")
        return 0;

    write("You smell the buttercups. Very nice!\n");
    say(QCTNAME(this_player()) + " smells on some buttercups.\n");

    return 1;
}
