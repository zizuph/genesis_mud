/*
 *  /d/Gondor/guilds/rangers/hq/vantage3.c
 *
 *  A room for climbing to the Central Headquarters vantage point
 *
 *  Coded by Alto, 20 June 2001
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public int move_ranger(object tp);

void
create_gondor()
{
    vantage_extraline();

    set_short("somewhere in the trees of the Druedain forest");
    set_long(long_desc());

    vantage_add_cmds();
    vantage_add_items();

    reset_room();
}

int
move_ranger(object tp)
{
    say(QCTNAME(tp) + " disappears into the branches.\n");
    TP->move_living("M", RANGERS_HQ_DIR + "vantage4", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " suddenly "
        + "emerges from the surrounding branches.\n", tp);
    return 1;
}

