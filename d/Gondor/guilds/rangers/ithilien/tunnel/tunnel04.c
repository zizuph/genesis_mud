/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnel04.c
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
    set_long("Rock walls enclose a tunnel that leads " +
        "into darkness somewhere deep beneath Ithilien. The " +
        "passage levels out to the west and inclines upward to " +
        "the northeast.\n");

    add_item(({"tunnel", "narrow tunnel"}), &long());
    add_item(({"route", "escape route", "passage"}), "The passage " +
        "levels out to the west and inclines upward " +
        "to the northeast.\n");
    add_item(({"walls", "ceiling", "floor"}), "The floor, walls and " +
        "ceiling are delved from solid rock.\n");
    add_item(({"rock", "stone"}), "The tunnel is " +
        "dug into solid rock, delving deep under Ithilien.\n");

    add_exit(RANGERS_ITH_TUNNEL + "tunnel03","northeast", &check_ranger());
    add_exit(RANGERS_ITH_TUNNEL + "tunnel05","west", &check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}

