/*
 * cadu_b1.c
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
    set_short("Pier");
    set_long("You are on the pier south of Cadu.\n" +
             "To the north are the shore and further north " +
             "you see the central parts of Cadu. " +
             "The pier continues to the south. " +
             "This is the place where the public galleon lands.\n");

    add_exit("cadu_s1", "north");
    add_exit("cadu_b4", "south");

    BEACH;

    clone_object("/d/Genesis/start/human/obj/sign")->move(TO);
}
