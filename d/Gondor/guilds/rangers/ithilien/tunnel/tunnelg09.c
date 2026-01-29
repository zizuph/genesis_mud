/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnelg09.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, April 14, 2004
 *
 *
 */
inherit "/d/Gondor/std/room.c";


#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"

int push_trapdoor();

void
create_gondor()
{
    set_short("a narrow tunnel");
    set_long("The rock walls enclose a tunnel that leads " +
        "into darkness to the east. Steps are carved into the " +
        "rock leading up.\n");
    add_item(({"tunnel", "narrow tunnel", "passage"}), &long());
    add_item(({"walls", "floor"}), "Solid rock walls " +
        "surround the tunnel.\n");
    add_item(({"rock", "stone"}), "The tunnel is " +
        "dug into solid rock.\n");
    add_item("steps", "Rough steps are carved directly into the " +
        "rock wall, leading up to the ceiling of the cave.\n");
    add_item("ceiling", "The ceiling is all rock, but you feel " +
        "you might be strong enough to push it.\n");

    add_exit(RANGERS_ITH_TUNNEL + "thicket_entrance","push", 
        &push_trapdoor(), 0, 1);
    add_exit(RANGERS_ITH_TUNNEL + "tunnelg08","east", &check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}

int
push_trapdoor()
{
    write("You push against the rock ceiling and " +
        "suddenly it opens.\nYou emerge into the forest.\n");
    return 0;
}

    


