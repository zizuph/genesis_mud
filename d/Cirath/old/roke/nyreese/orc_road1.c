/*
 * orc_road1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("path next to the sea");
    set_long("You are standing on a small path next to the sea.\n" +
             "To the west you can see some roofs above the trees, " +
             "and southwest of you is the outer parts of the harbour " +
             "of Cadu clearly visible far out in the ocean. " +
             "The path leads west to the sand beach south of Cadu " +
             "and east further into the woods.\n");

    add_exit("cadu_s5", "west");
    add_exit("orc_road2", "east");

    BEACH;
}
