/*
 * tree1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("treetop");

    set_long("You are in the top of a huge tree, surrounded by leaves and " +
             "thick branches. The wind blows from the sea, making the tree " +
             "move in a slightly uncomfortable way below you.\n");

    add_exit("f4", "down");

    reset_room();
}

void
reset_room()
{
    if (present("herb"))
        return;
    tell_room(TO, "A small leaf falls from one of the branches.\n");
    clone_object(ROKEDIR + "obj/redwood")->move(TO);
}
