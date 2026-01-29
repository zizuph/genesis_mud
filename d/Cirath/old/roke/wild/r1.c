/*
 * r1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
reset_room()
{
    if (present("buttercups", TO))
        return;

    tell_room(TO, "Some flowers grow from the ground.\n");
    clone_object(ROKEDIR + "obj/buttercups")->move(TO);
}

void
create_room()
{
    set_short("on a small road");
    set_long("You are standing on a small road leading towards the mountains. " +
             "The forest is somewhat thick here, but obviously there must be " +
             "something important further to the east, because the road looks " +
             "well-used.\n");

    add_exit("fa", "southwest");
    add_exit("r2", "east");
    add_exit("d1", "north");
    reset_room();
}
