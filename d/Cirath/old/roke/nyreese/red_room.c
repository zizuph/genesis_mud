/*
 * red_room.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("a nice room");
    set_long("You are in a nice room, with a thick red carpet, mirrors " +
             "everywhere, and a huge comfortable bed in the middle of the " +
             "floor.\n");
    add_exit("red_bordell", "out", "@@block");
}

void
block()
{
    write("The lady is very disappointed at you, leaving now in the " +
          "middle of the action.\n");
    (NYREESEDIR + "red_bordell")->remove();
    return 0;
}

int
baba()
{
    if (this_player()->query_wiz_level())
        return 0;

    if (query_verb() == "out")
        return 0;

    write("You are much to busy to do that.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(baba, "", 1);
}
