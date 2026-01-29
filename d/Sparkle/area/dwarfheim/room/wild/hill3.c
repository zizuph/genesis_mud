/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("The other side of the rift");
    set_long("You are at the highest point of a small hill. To the north the\n"+
             "way is blocked by a deep rift, and south and west some large\n"+
             "rocks stops all travelling. It seems like the only way out of\n"+
             "here is where you came from, to the east.\n");

    add_item("boulder","It is huge and grey.\n");
    add_item(({"rock", "rocks"}), "These rocks prevent travel to the south and west.\n");

    add_exit ("forest5","east");
}

