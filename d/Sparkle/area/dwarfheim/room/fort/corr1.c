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
    set_short("Stone tunnel in Dwarfheim");
    set_long("You are in a huge stone tunnel leading through Dwarfheim.\n"+
             "To the north of you is the local shop, and to the west is\n"+
             "the roaring waterfall that hides the entrance to the cave\n"+
             "system.\n");
    add_item("tunnel", "It is very large and crafted from stone.\n");
    add_item("shop", "A nice place to sell your wares.\n");
    add_item("waterfall", "It forms a thin, but effective, water curtain just\n"+
             "outside the entrance to Dwarfheim.\n");
    add_item("entrance", "This is where you enter the cave system.\n");
    add_exit ("shop","north");
    add_exit (S_AREA_ROOM_DIR + S_AREA_WILD + "entr","west");
    add_exit ("corr2","east");

    I;
}

