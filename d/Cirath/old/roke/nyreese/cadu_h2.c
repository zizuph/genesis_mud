/*
 * cadu_h2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

void reset_room();

void
create_room()
{
    INSIDE;

    set_short("Inside a small shed.\n");
    set_long("This is a small fisherman's shed. It contains various " +
             "fishing equipment. Some rotten fish are stashed in a corner.\n");

    add_item("fish","It smells truly vile. You wish you hadn't done that!\n");

    add_exit("cadu_s2", "south");

    reset_room();
}

void
reset_room()
{
    seteuid(getuid(TO));
    if(!present("rope", TO))
        clone_object("/std/rope")->move(TO);
  
    if(!present("net", TO))
        clone_object(ROKEDIR + "obj/fishingnet")->move(TO);

    tell_room(TO, "As your eyes adapt to the darkness you notice a fishing " +
              "net in one of the corners of the shed.\n");
}
