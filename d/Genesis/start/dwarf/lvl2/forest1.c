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
    set_short("In a thick forest");
    set_long("You are in a thick forest. The trees around you tower high\n"+
             "up in the sky. As you walk on the path you feel your feet\n"+
             "sinking a few inches down into the mud.\n");

    add_item("mud","It is a little too dry to throw at someone.\n");
    add_item("trees","They are pines.\n");

    add_exit(LVL2+"hill1","west");
    add_exit(LVL2+"forest3","east");
}

