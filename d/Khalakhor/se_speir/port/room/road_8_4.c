/*
 * This is part of a road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit ROADBASE;

object *guards;

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
                guards[i]->set_wanderer();
                guards[i]->set_team_leader();
            }
            else
                guards[i]->set_team_follower();
            guards[i]->set_team_name("centre_team");
            guards[i]->set_autoassist();
            guards[i]->arm_me();
            guards[i]->move(TO);
            tell_room(this_object(),
                capitalize(guards[i]->short()) + " arrives.\n");
        }
    }
}

public string
query_dir_to_jail()
{
    return "north";
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading " +
        "north and south near the middle of the " +
        "village. The road is flanked on both sides " +
        "by high stone walls, but a wide gateway " +
        "leads through the east wall into what appears " +
        "to be the town hall.\n");

    add_exit(ROOM + "road_8_3", "north");
    add_exit(ROOM + "th_1", "east");
    add_exit(ROOM + "road_8_5", "south");
    reset_room();
}
