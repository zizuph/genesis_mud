/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnel01.c
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
        "into darkness. It appears to be an ancient " +
        "passage, escavated deep into the rock. The River Anduin " +
        "must be nearby, judging from the sound of rushing water.\n");
    add_item(({"tunnel", "narrow tunnel", "passage"}), &long());
    add_item(({"walls", "rock walls"}), "Solid rock walls surround " +
        "the tunnel.\n");

    add_item(({"rock", "stone"}), "The tunnel is " +
        "dug into solid rock, delving deep under Osgiliath. Perhaps " +
        "in ancient times it functioned as a sewer.\n");
    add_item(({"Anduin", "river", "nearby Anduin", "anduin"}), "The " +
        "tunnel must go below the river, since you can hear the rushing " +
        "sound of water overhead. Hopefully it will not leak.\n");

    add_exit(RANGERS_ITH_TUNNEL + "tunnel11","west", &check_ranger());
    add_exit(RANGERS_ITH_TUNNEL + "tunnel09","northeast", &check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}

