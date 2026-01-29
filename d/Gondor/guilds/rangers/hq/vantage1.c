 /*
 *  /d/Gondor/guilds/rangers/hq/vantage1.c
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
public int enter_hideout();

void
create_gondor()
{
    vantage_extraline();

    set_short("somewhere in the trees of the Druedain forest");
    set_long(long_desc() + "There is a small window opening into the hideout "
        + "here.\n");

    vantage_add_cmds();
    vantage_add_items();

    add_item(({"hideout", "building"}), "Most of the building is hidden "
        + "among the trees. From here you can only see part of the east "
        + "wall.\n");
    add_item(({"wall", "east wall"}), "The wall is constructed of wood "
        + "and shingle. Most of it is obscured by the trees, but from here "
        + "you can see a small window.\n");
    add_item(({"wood", "shingle", "shingles"}), "The wall is made of wood "
        + "milled from the very forest about you. There are also wooden "
        + "shingles nailed to the wall, protecting it from the elements.\n");
    add_item(({"window", "small window"}), "The small window looks just "
        + "large enough to slip through.\n");

    add_cmd_item(({"window", "through window", "small window", 
        "through small window"}), "slip", &enter_hideout());

    reset_room();
}

int
move_ranger(object tp)
{
    say(QCTNAME(tp) + " disappears into the branches.\n");

    TP->move_living("M", RANGERS_HQ_DIR + "vantage2", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " suddenly "
        + "emerges from the surrounding branches.\n", tp);

    return 1;
}

int
enter_hideout()
{
    object tp = this_player();

    write("You slip quietly through the small window.\n");
    say(QCTNAME(tp) + " slips quietly through the small window.\n");
    TP->move_living("M", RANGERS_HQ_DIR + "ucorridor2", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " slips quietly "
        + "in through the small window.\n", tp);
    return 1;
}

