/*
 *  /d/Gondor/guilds/rangers/ithilien/vantage1.c
 *
 *  A passage carved into the stone of Henneth Annun
 *
 *  Coded by Alto, 22 July 2001
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "exit.c"

public int move_ranger(object who);

void
create_gondor()
{
    vantage_extraline();

    set_short("In a small passage");
    set_long(long_desc() + "You can also go back down from here.\n");

    vantage_add_cmds();
    vantage_add_items();

    add_exit(RANGERS_ITH_DIR + "window", "down", &check_ranger());
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}

int
move_ranger(object who)
{
    set_this_player(who);

    say(QCTNAME(who) + " reaches a higher point in the passage.\n");
    tell_room(RANGERS_ITH_DIR + "vantage2", QCTNAME(who) + " arrives from "
        + "below.\n", ({who}));

    who->move_living("M", RANGERS_ITH_DIR + "vantage2", 1, 0);
    return 1;
}

