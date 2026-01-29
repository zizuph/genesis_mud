/*
 * sh1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("south of a road");
    set_long("You are in an unusually featureless place, south of a small road. " +
             "There is absolutely nothing of interest here, and you wonder " +
             "if the Creator had a headache when she created this place.\n");

    add_exit("r2", "north");
    add_exit("sh2", "south");

    reset_room();
}

void
reset_room()
{
    if (!present("log", TO))
    {
        clone_object(ROKEDIR + "obj/log")->move(TO);
        tell_room(TO,
                  "A small dragon flies by and drops a log on your head. \n");
    }
}
/* apa spy!!! */
