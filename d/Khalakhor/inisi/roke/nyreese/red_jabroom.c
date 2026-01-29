/*
 * red_jabroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object jab;

void reset_room();

void
create_room()
{
    set_short("a nice meadow");
    set_long("You are standing in a nice, sunny meadow, which is " +
             "dominated by a huge tree.\n");
    add_item("tree", "It's a Tumtum tree. You find a nice spot between " +
             "its huge roots, which looks suitable for resting.\n");
    add_cmd_item("tree", "climb", "It is too difficult.\n");

    add_exit("red_r5", "north");
    reset_room();
}

int
rest()
{
    write("You sit down between the roots and rest for a while.\n");
    say(QCTNAME(TP) + " rests on the ground.\n");

    return 1;
}

void
init()
{
    ::init();

    add_action(rest, "rest");
}

void
reset_room()
{
    if (jab)
        return;

    seteuid(getuid(TO));

    jab = clone_object(ROKEDIR + "npc/jab");
    jab->move(TO);
    tell_room(TO, "A fierce Jabberwock leaps out of the shadows!\n");
}
