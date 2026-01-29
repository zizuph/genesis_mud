#pragma strict_types

#include "defs.h"
#include <ss_types.h>

inherit STDROOM;

public void
create_room()
{
    set_short("on a narrow ledge in a ravine");
    set_long("You are on a narrow, rocky ledge jutting from " +
        "the side of a cliff face, overlooking a dead forest " +
        "in the bottom of a ravine. The forest spreads out " +
        "to the south, a massive wall of dead trees covered " +
        "in beards of dark grey and green mosses. Beneath " +
        "you lies nothing but tangled underbrush strewn with " +
        "chunks of stone, and a good long way down, too. " +
        "You look for handholds, but it looks to be impossible " +
        "to climb down from here. Looking back up, you can " +
        "see part of a ruined tower sticking out from the edge " +
        "of the cliff high above you. You might not be able " +
        "to climb down, but you think you can make it back up " +
        "to the cliff top beside the tower.\n\n");

    add_item(({"forest", "trees", "dead trees"}),
        "Spreading out to the north, a massive forest of dead "+
        "or dying trees turns this ravine into a floral graveyard.\n");
    add_item(({"tower", "ruins"}),
        "Far above your head, at the top of the cliff, the remains " +
        "of a partially-intact tower jut out into view.\n");
}

public int
do_climb(string str)
{
    notify_fail("Climb where?\n");

    if (!str || !strlen(str))
        return 0;

    if (str != "up" &&
        str != "cliff" &&
        str != "up cliff" &&
        str != "to tower")
    {
        return 0;
    }

    if (TP->query_skill(SS_CLIMB) < (20 + random(20)))
    {
        write("You try to climb up the side of the cliff, " +
            "but you just can't make it!\n");
        say(QCTNAME(TP) + " tries to climb up the side of " +
            "the cliff, but just can't seem to make it!\n");
        return 1;
    }
    else
    {
        write("You manage to find some good handholds, and " +
            "work your way up to the top of the cliff.\n");
        say(QCTNAME(TP) + " manages to find some good handholds, " +
            "and works " + TP->query_possessive() + " way up " +
            "to the top of the cliff.\n");
        TP->move_living("M", FOREST + "n_forest_1", 1, 0);
        say(QCTNAME(TP) + " scrambles up the side of the cliff " +
            "onto the forest floor.\n");
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}
