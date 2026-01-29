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

#include "../defs.h"

object guard1,guard2;

void
reset_room()
{
    if (guard1 || guard2)
        return;

    guard1 = clone_object(D_MON+"guard");
    guard1->arm_me();
    guard1->move(TO);
    guard2 = clone_object(D_MON+"guard");
    guard2->arm_me();
    guard2->move(TO);
}

void
create_room()
{
    set_short("Royal palace");
    set_long("You are in a huge hall inside the Royal Palace of Dwarfheim.\n"+
             "Here, the dwarves gather to request audiences with the king,\n"+
             "or to donate something in the charity box standing in the corner.\n"+
             "East of you, you can see an open door leading into the throne-room\n"+
             "of the King, and to the south is another impressive-looking room.\n");

    add_exit(LVL1+"palace3","east");
    add_exit(LVL1+"palace1","south");

    add_item("hall", "IT is very large and is carved from stone.\n");
    add_item("door","It is an ordinary mithril door.\n");

    seteuid(getuid(TO));

    room_add_object(D_OBJ+"charity");

    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}
