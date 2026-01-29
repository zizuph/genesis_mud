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
    set_short("An edge, near the top of a hill");
    set_long("You are on the edge of a high mountain, just north of a small "+
             "cliff. The view is stunning from here, and deep below you, you "+
             "spot a small river flowing through the valleys.\n");

    add_exit(LVL2+"hill1","south");
    add_exit(LVL2+"edge2","west");
}

