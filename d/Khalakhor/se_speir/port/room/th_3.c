/*
 * th_3.c
 *
 * This is the reception room for the town hall of port macdunn.
 *
 * Khail - June 4/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#define TO this_object()

inherit "/d/Khalakhor/std/room";

object *guards;

public int *
query_local_coords()
{
    return ({9,4});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: reset_room
 * Description  : Resets the room, ensures guards
 *                are present.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    int i;

    if (!guards)
        guards = allocate(4);

    for (i = 0; i < sizeof(guards); i++)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(NPC + "guard");
        
            if (i == 0)
            {
                guards[i]->set_team_leader();
            }
            else
                guards[i]->set_team_follower();
            guards[i]->set_team_name("fahlmar_guard_team");
            guards[i]->set_autoassist();
            guards[i]->arm_me();
            guards[i]->move(TO);
            tell_room(this_object(),
                capitalize(guards[i]->short()) + " arrives.\n");
        }
    }
}

public void
create_khalakhor_room()
{
    set_short("reception room");
    set_long("   You've entered the main reception room for " +
        "visitors waiting to see the Lord of Port Macdunn. " +
        "Richly polished wood panels on the walls give the " +
        "room a slightly orange tinge. During busier times, " +
        "he'd hire someone to filter through petitioners and " +
        "send them in one at a time, but there's been no " +
        "need for that in years, and the door to his main " +
        "office stands wide open to the east.\n");

    add_item(({"walls"}),
        "The walls of the building a covered in well crafted "+
        "wooden panels.\n");
    add_item(({"panels", "wooden panels"}),
        "The panels are the product of a master carpenter, "+
        "quite possibly made from oak.\n");
    add_item(({"walkway"}),
        "You can't see much of it from here, but " +
        "it leads out into the street.\n");
    add_item(({"ground", "floor"}),
        "The floor of the room has been constructed from " +
        "tightly-jointed planks.\n");
    add_item(({"planks"}),
        "Judging from the amount of wear, this room " +
        "receives both a lot of visitors, as well as " +
        "upkeep to maintain the strength of the flooring.\n");
    add_item(({"ceiling"}),
        "The ceiling is lightly arched, and covered in " +
        "the same panels which adorn the walls.\n");

    INSIDE;

    add_exit(ROOM + "th_6", "east");
    add_exit(ROOM + "th_2", "south");

    reset_room();
}
