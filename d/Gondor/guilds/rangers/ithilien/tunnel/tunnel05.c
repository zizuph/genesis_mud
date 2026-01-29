/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnel05.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, March 25, 2004
 *
 *
 */
inherit "/d/Gondor/std/room.c";


#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"

void
create_gondor()
{
    set_short("a narrow tunnel");
    set_long("The rock walls enclose a tunnel that leads " +
        "down into darkness. It appears to be an ancient " +
        "escape route from the hideout, escavated deep into " +
        "the rock under Ithilien. The passage leads steeply down " +
        "to the west and inclines upward to the east.\n");

    add_item(({"tunnel", "small tunnel", "passage"}), &long());
    add_item(({"walls"}), "The solid rock walls surround the tunnel.\n");
    add_item(({"rock", "stone"}), "The tunnel is " +
        "dug into solid rock, delving deep under Ithilien.\n");

    add_exit(RANGERS_ITH_TUNNEL + "tunnel04","east", &check_ranger());
    add_exit(RANGERS_ITH_TUNNEL + "tunnel06","down", &check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}

