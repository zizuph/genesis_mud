/*
 * cadu_s5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_room()
{
    set_short("Shore");
    set_long("This is the eastmost part of the inhabitated areas of " +
             "Cadu. It also happens to be the Cadu beach, where " +
             "the locals are enjoying the warmth of the sun lying in " +
             "the sand. There is a nice spot free, suitable for sunbathing. " +
             "To the east, a small path leads towards the wilderness.\n");
  
    add_item("sand",   "The sand is white and hot from the sun.\n");
    add_item("people", "Most of them have a nice tan.\n");
    add_item("spot",   "Here you can sunbathe for a while.\n");

    add_exit("cadu_s1",   "west");
    add_exit("orc_road1", "east");

    BEACH;
}

int
bath()
{
    write("You lie down for a short while, and when you rise you have "+
          "a nice tan.\n");
    say(QCTNAME(TP) + " sunbathes for a while.\n");
    TP->add_prop(LIVE_S_SOULEXTRA, "tanned");

    return 1;
}

void
init()
{
    ::init();
    add_action(bath, "sunbathe");
    add_action(bath, "sunbath");
    add_action(bath, "tan");
}
