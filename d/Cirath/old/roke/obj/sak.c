/*
 * sak.c
 *
 * Used in wild/dc1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"

void
create_object()
{
    set_short("black pearl");
    set_name("pearl");
    add_name("gresgrej1");
    set_adj("black");
    set_long("For a short moment you think you see the image of a great wizard\n" +
             "inside the pearl, but you decide that it was only your imagination.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 333);
    add_prop(OBJ_I_VALUE, 742);
}

void
init()
{
    ::init();
    add_action("stare", "stare");
}

int
stare(string s)
{
    if (s != "into pearl")
        return 0;

    write("You stare into the pearl and feel that the universe has communicated with you.\n");
    return 1;
}
