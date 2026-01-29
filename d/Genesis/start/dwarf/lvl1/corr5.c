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

object dv;

#include "../defs.h"

void reset_room();

string
sign()
{
    return "The Staggering Dwarf Pub. 50 m down from here.\n";
}

void
create_room()
{
    set_short("Stone corridor");
    set_long("You are standing in a long corridor leading east-west through\n"+
             "the mountain. A small tunnel leads downwards from here, into\n"+
             "a dark cave deep inside the mountain. To the north another\n"+
             "tunnel goes towards the temple of Dwarfheim.\n"+
             "A small sign points downwards.\n");

    add_item("corridor", "It seems very long.\n");
    add_item("tunnel", "It is carved from stone.\n");
    add_item("cave", "It seems pretty far down.\n");
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");

    add_exit(LVL1+"square","east");
    add_exit(LVL1+"corr4","west");
    add_exit(LVL3+"pub","down");
    add_exit(LVL1+"corr6","north");

    I;

    reset_room();
}

void
reset_room()
{
    if(dv)
        return;

    dv = clone_object(D_MON + "citizen");
    dv->arm_me();
    dv->move_living("singing a merry tune.\n",TO);
}
