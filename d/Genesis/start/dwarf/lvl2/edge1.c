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
    set_short("Edge of a cliff");
    set_long("You are standing on the edge of a high cliff. A small path\n"+
             "leads down the mountainside, towards a ledge just beside\n"+
             "a roaring waterfall.\n");

    add_exit(LVL1+"entr","down");
    add_exit(LVL2+"edge2","north");
    add_exit(LVL2+"hill1","east");
}


