/*
 *  /d/Gondor/guilds/rangers/north/vantage5.c
 *
 *  A ruined stairwell in the Northern hideout
 *
 *  Coded by Alto, 17 July 2001
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public int move_ranger(object who);

void
create_gondor()
{
    vantage_extraline();

    set_short("in a ruined stairwell");
    set_long(long_desc());

    add_item(({"stairwell", "room"}), &long_desc());

    vantage_add_cmds();
    vantage_add_items();

    reset_room();
}

int
move_ranger(object who)
{
    say(QCTNAME(who) + " reaches a higher point on the stairwell.\n");

    who->move_living("M", RANGERS_NOR_DIR + "vantage_top", 1, 0);
    tell_room(RANGERS_NOR_DIR + "vantage_top", QCTNAME(who) + " arrives from "
        + "below.\n", who);

    return 1;
}

