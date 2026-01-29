/*
 * t1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

string
mylong()
{
    string s;
    s = "You have managed to crawl deep into the mountain. It is rather " +
        "narrow here, but fortunately it is not too narrow for you to be " +
        "able to turn around.\n";

    if (present("rubble", TO))
        return s + "There is one obvious exit: west.\n";
    else
        return s + "There are two obvious exits: west, east.\n";
}

void
reset_room()
{
    if (!present("rubble", TO))
        clone_object(ROKEDIR + "obj/rubble")->move(TO);
}

void
create_room()
{
    set_short("rift");
    set_long("@@mylong");

    DARK;
    INSIDE;

    set_noshow_obvious(1);

    add_exit("c4", "west");
    add_exit("dc1", "east", "@@block");

    reset_room();
}

int
block()
{
    if (present("rubble", TO))
    {
        write("There is no obvious exit east.\n");
        return 1;
    }
    write("You crawl east and fall down into another room.\n");
    return 0;
}
