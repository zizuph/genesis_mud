/*
 * sandcastle.c
 *
 * Used in nyreese/cadu_s3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("castle");
    set_adj("sand");
    set_long("It is a mighty sand castle that someone has built on the shore, " +
             "and is so large that it even might be possible to enter it.\n");
    set_short("sand castle");
    
    add_prop(OBJ_I_NO_GET, "Get a sandcastle? No way!\n");
}

int
enter(string s)
{
    NF("Enter what?\n");

    if (s != "castle")
        return 0;

    TP->move_living("into the castle", NYREESEDIR + "sandcastle");

    return 1;
}

void
init()
{
    ::init();
    add_action(enter, "enter");
}

