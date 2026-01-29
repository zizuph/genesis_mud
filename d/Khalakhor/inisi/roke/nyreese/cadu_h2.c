/*
 * cadu_h2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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

    set_short("Inside a small shed");
    set_long("This is a small fisherman's shed. It contains various " +
             "fishing equipment. Some rotten fish are stashed in a corner.\n");

    add_item("fish","It smells truly vile. You wish you hadn't done that!\n");

    add_exit("cadu_s2", "south");

    reset_room();
}

void
reset_room()
{
    object net;
    int cloned = 0;

    seteuid(getuid(TO));
    if (!present("rope", TO))
    {
        clone_object("/std/rope")->move(TO);
        cloned = 1;
    }
  
    if (!objectp(net = present("net", TO)))
    {
        net = clone_object(ROKEDIR + "obj/fishingnet");
        net->move(TO);
        cloned = 1;
    }
    net->reset_net();

    if (cloned)
        tell_room(TO, "As your eyes adapt to the darkness you notice a " +
                  "fishing net in one of the corners of the shed.\n");
}
