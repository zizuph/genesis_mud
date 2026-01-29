/*
 * cas_c1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You find yourself in a corner of the mighty castle. " +
             "The walls here on this level are painted in dark colors. " +
             "If it hadn't been for the magical light that the ceiling " +
             "is emitting you probably wouldn't see anything...\n" +
             "To your south you see a quite ordinary exit and to your east " +
             "you think you can see some guards eating or something. The " +
             "exit to your northwest looks like an entrance to a tower.\n");

    add_exit("cas_t31", "northwest");
    add_exit("cas_c2", "east");
    add_exit("cas_c5", "south");
}
