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
    set_short("Small path, leading through the forest");
    set_long("You are on a small path, leading through the forest, from\n"+
             "the north to the south, or the other way around, depending\n"+
             "where you come from. It really smells nice here, and as you\n"+
             "look around, you spot a huge field of flowers.\n");

    add_item("flowers","They are really beautiful, and colored in different colors.\n");

    add_exit ("forest3","north");
    add_exit ("forest6","south");
}

