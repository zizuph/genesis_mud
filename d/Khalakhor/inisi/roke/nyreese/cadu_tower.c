/*
 * cadu_tower.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include "bridgedefs.h"

#define DIVES 3
string *divestower=({"dives into the water", "slips and falls into the water",
                     "turns a somersault into the water"});
string *divesyou=({"dive into the water", "slip and fall into the water",
                   "turn a somersault into the water"});
string *divesother=({"dives from the tower", "slips and falls from the tower",
                     "turns a somersault from the tower"});

void
create_room()
{
    set_short("Diving tower");
    set_long("This is the diving tower of Cadu.\n" +
             "Below you to the east is a pier and far to " +
             "the north you see the village. " +
             "The water below looks inviting.\n");

    add_exit("cadu_b3", "down");

    BEACH;
}

int
do_dive(string str)
{
    int style;

    if (!str || str == "")
    {
        if (TP->query_skill(SS_SWIM) < DONTDIVE)
        {
            write("You do not dare to dive when you're such a lousy swimmer.\n");
            return 1;
        }

        style = random(DIVES);
        write("You " + divesyou[style] + ".\n");
        say(QCTNAME(TP) + " " + divestower[style] + ".\n");
        tell_room(WATERROOM,  QCNAME(TP) + " " + divesother[style] + ".\n");
        tell_room(BRIDGEROOM, QCNAME(TP) + " " + divesother[style] + ".\n");
        
        TP->move_living("M", WATERROOM);
 
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_dive, "dive");
    add_action(do_dive, "bath");
}
