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

object duck;

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("Damp corridor");
    set_long("You are standing in the middle of a damp corridor through\n"+
             "the Dwarfheim mountain. To the north is an entrance leading\n"+
             "into the local post office.\n");

    add_item("corridor", "This is a damp, dark corridor.\n");
    add_item("post office", "You can send mail there.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit ("corr2","south");
    add_exit (S_DOMAIN_START_DIR + "dwarf/post","north","@@block");
    add_exit ("corr4","east");

    reset_room();
}

void
reset_room()
{
    if(duck)
        return;

    setuid (); seteuid (getuid ());
    duck = clone_object(S_LOCAL_NPC_DIR + "duck");
    duck->move_living("sfd",TO);
}

int
block()
{
    if(!interactive(TP))
        return 1;
    return 0;
}

