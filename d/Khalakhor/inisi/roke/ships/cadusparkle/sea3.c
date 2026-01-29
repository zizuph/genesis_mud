/*
 * sea3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../../defs.h"

void
create_room()
{
    set_short("Sea");
    set_long("You are in the open sea. A small volcano island is\n" +
             "visible northeast of here, very far away.\n");
    WATER;
}
