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

inherit "/std/room";

object dverg;

#include "../defs.h"

void
create_room()
{
    set_short("Tunnel in the dwarven mountain");
    set_long("You are standing in a dimly-lit tunnel leading through the\n"+
             "dwarven mountain. In front of you, to the east, is the\n"+
             "local Adventurer's Guild, and to the west and north the\n"+
             "tunnel continues through the mountain.\n");

    add_item("tunnel", "It looks very dim.\n");
    add_item(({"Adventurer's Guild", "adventurer's guild", "guild", "Guild"}), "This "+
    "looks like the perfect place to train your abilities.\n");
    add_exit(LVL1+"guild","east");
    add_exit(LVL1+"corr1","west");
    add_exit(LVL1+"corr3","north");

    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

void
reset_room()
{
    if(dverg)
        return;

    dverg = clone_object(D_MON+"citizen");
    dverg->arm_me();
    dverg->move_living("from nowhere",TO);
}
