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
    set_short("On a small slope, leading towards the top of a hill");
    set_long("You are on a small slope, leading towards the top of\n"+
             "the hill south of here. The sun shines brightly, and\n"+
             "the air is rather warm. You hear some birds in the thick\n"+
             "forest east of here.\n");

    add_exit ("hill2","south");
    add_exit ("forest1","east");
    add_exit ("edge3","north");
    add_exit ("edge1","west");
}

