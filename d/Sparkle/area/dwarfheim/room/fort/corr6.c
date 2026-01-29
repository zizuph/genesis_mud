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
    set_short("Intersection");
    set_long("You are standing in the middle of a three-way intersection.\n"+
             "North of you, you vaguely spot something reminding you of\n"+
             "a bulletin board. Some dwarves are gathered there, and\n"+
             "occasionally you hear pieces of their discussion about life, the\n"+
             "universe and everything. Another corridor leads west from here\n"+
             "and if you go south you will come to the main route through\n"+
             "the mountain.\n");

    add_item("dwarves", "They seem quite busy.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit ("board","north");
    add_exit ("corr7","west");
    add_exit ("corr5","south");
}

