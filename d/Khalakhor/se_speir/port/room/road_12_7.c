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
            guards[i]->set_team_name("bladesmith_team");
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
    return "east";
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading east " +
        "and west through the interior of Port Macdunn. " +
        "The road forms a T-intersection here, with a " +
        "stretch leading away northwards. " +
        "The south side of the road is enclosed by the walls " +
        "of buildings as far as you can see, but there's a " +
        "wide spread of grass beside the low stone building " +
        "on the north side of the road a stone's throw " +
        "to the west.\n");

    add_exit(ROOM + "road_12_6", "north");
    add_exit(ROOM + "road_13_7", "east");
    add_exit(ROOM + "road_11_7", "west");
    reset_room();
}
