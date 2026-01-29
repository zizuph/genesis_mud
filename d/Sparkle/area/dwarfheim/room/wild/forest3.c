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
    set_short("Forest");
    set_long("You are now deep inside the forest. The trees are very tall,\n"+
             "and occasionally you spot an animal moving in the thick, dark\n"+
             "vegetation. Somehow this doesn't seem to be the most pleasant\n"+
             "place to spend a Sunday afternoon.\n");

    add_exit ("forest1","west");
    add_exit ("forest4","south");
}

