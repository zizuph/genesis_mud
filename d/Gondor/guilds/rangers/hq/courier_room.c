/*
 *   /d/Gondor/guilds/rangers/hq/courier_room.c
 *   
 *   A non-descript room for courier animals.
 *
 *   Alto, 25 July 2001
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"

void
create_gondor()
{
    set_short("a small room");
    set_long("Not much here but a few ferrets and pigeons "
        + "milling about with nothing to do.\n");

}
