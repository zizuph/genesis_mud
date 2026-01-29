/*
 * cadu_b4.c
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
    set_long("You are standing in the middle of the pier south of Cadu.\n" +
             "To the north you can see a nice beach and a few people and " +
             "to the south the pier continues until it makes a turn " +
             "to the west.\n");
   
    add_my_desc("The pier has been damaged, and no ships can " +
                "land here.\n");
   
   
    add_exit("cadu_b1", "north");
    add_exit("cadu_b2", "south");
   
    BEACH;
}
