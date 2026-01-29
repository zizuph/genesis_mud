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
    set_short("A sunny meadow");
    set_long("This is a small sunny meadow in the forest. Just west of here,\n"+
             "you think that you see the end of the forest.\n");

    add_exit(LVL2+"hill2","west");
}


