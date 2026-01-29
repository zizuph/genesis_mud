/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_std_herbs("underground");

    set_short("Inside a large cave");
    set_long("The cave is large and is inside a large mountain. It gapes " +
        "out into the open but the back leads into thick darkness. The " +
        "cave looks like it was naturally carved by the elements. It looks " +
        "like you can climb up in the cave or leave by going west.\n");

    reset_room();

    add_exit("/d/Faerun/highroad/rooms/htr08", "west");
    add_exit(TUN_DIR + "cv02", "down");
}
void
init()
{
    ::init();
    write("A gust of mountain wind blows against you.\n");
    say("A gust of mountain wind blows against " + QTNAME(TP) + ".\n");
}

int climb()
{
    if(TP->query_skill(SS_CLIMB) < 30)
    {
        write("You slip while trying to climb up in the cave.\n");
        write("Unfortunately you fall backwards and slam into the cave's floor!\n");
        TP->heal_hp(-250);
        say(QCTNAME(TP) + " slipped while trying to climb up in the cave, and " +
            "falls backwards and slams into the ground.\n");
        return 1;

        if (TP->query_hp() < 1)
            TP->do_die(TO);
    }
    write("You manage to climb up in the cave.\n");
    say(QCTNAME(TP) + " manages to climb up in the cave.\n");
    return 0;
}

void
reset_room()
{
    set_searched(0);
}
