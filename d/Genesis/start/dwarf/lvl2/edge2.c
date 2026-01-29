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

#include "../defs.h"

void
create_room()
{
    set_short("On the edge of a steep cliff");
    set_long("This is a small spot on top of a huge mountain. To the west\n"+
             "and north is only air, with a shimmering river deep below in\n"+
             "the valley.\n");

    add_exit(LVL2+"edge1","south");
    add_exit(LVL2+"edge3","east");
}

