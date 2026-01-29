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
    set_short("Edge of forest");
    set_long("This is the edge of a vast forest. North and west of here\n"+
             "paths lead into the forest, between the trees. Small birds\n"+
             "fly above you, and their singing makes you feel very happy.\n");

    add_exit(LVL2+"forest4","north");
    add_exit(LVL2+"forest5","west");
    add_exit(LVL2+"forest7","east");

    add_item("birds","They sing beautifully.\n");
}
