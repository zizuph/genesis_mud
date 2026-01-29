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

void reset_room();

void
create_room()
{
    set_short("On the top of a hill, north of a deep rift");  
    set_long("This is the top of a small hill. South of here, a deep\n"+
             "rift divides the mountain in two, and to the east grows"+
             " a vast forest.\n");

    add_exit(LVL2+"forest2","east");
    add_exit(LVL2+"hill1","north");

    reset_room();
}

void
reset_room()
{
    if(!present("hill",TO))
    {
        clone_object(D_MON+"anthandler")->move(TO);

        tell_room(TO,"A huge ant enters, drops an ant hill, and leaves again.\n");
    }
}
