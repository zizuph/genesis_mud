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

void reset_room();

object dv;

void
create_room()
{
    set_short("Dark corner");
    set_long("You are in a dark corner somewhere in Dwarfheim. North of you\n"+
             "is the entrance to the local bank, and back east, where it\n"+
             "also is a lot more light, the tunnel continues towards the\n"+
             "centre of the village.\n");

    add_item("bank", "You may exchange money here.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit ("bank","north");
    add_exit ("corr6","east");

    reset_room();
}

void
reset_room()
{
    if(dv)
        return;

    setuid (); seteuid (getuid ());
    dv = clone_object(S_LOCAL_NPC_DIR + "citizen");
    dv->arm_me();
    dv->move_living("singing a merry tune.\n",TO);
}

