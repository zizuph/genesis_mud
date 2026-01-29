/*
 * This is the seventh room on first road in Port Macdunn, which
 * intersects here with the pier road.
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
            guards[i]->set_team_name("pier_team");
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
    set_short("harbourfront intersection");
    set_long("   You are in an intersection with roads leading " +
        "north, south, east and west. To the south lie the " +
        "piers of Port Macdunn, jutting out into Cala Fasgadh. " +
        "North from here, a wider, heavily used road heads " +
        "into the town proper. The road into town is flanked " +
        "on either side by low stone buildings. To the east and " +
        "west, the road follows the shoreline.\n");

    add_exit(ROOM + "road_9_8", "north");
    add_exit(ROOM + "road_10_9", "east");
    add_exit("/d/Khalakhor/ship/macdunn/pier1", "south");
    add_exit(ROOM + "road_8_9", "west");
    reset_room();
}
