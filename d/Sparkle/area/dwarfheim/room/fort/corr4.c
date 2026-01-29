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

#include "defs.h"

void
create_room()
{
    set_short("Corridor");
    set_long("This corridor is a little longer than the others and is\n"+
             "leading very deep into the mountain. Far away, to the\n"+
             "east and west, you see light openings.\n");

    add_item("openings", "You cannot seem to get your eyes to focus properly.\n");
    add_item("corridor", "It seems quite long.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit ("corr3","west");
    add_exit ("corr5","east");
}

