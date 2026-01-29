/*
 * jail.c
 *
 * 'jail' of Port MacDunn.
 *
 * Khail - March 30/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object *guards;

public int *
query_local_coords()
{
    return ({18,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public string
query_dir_to_jail()
{
    return "east";
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
                guards[i]->set_wanderer();
                guards[i]->set_team_leader();
            }
            else
                guards[i]->set_team_follower();
            guards[i]->set_team_name("jail_entrance_team");
            guards[i]->set_autoassist();
            guards[i]->arm_me();
            guards[i]->move(TO);
        }
    }
}
   
/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("prison of Port Macdunn");
    set_long("   You've entered a large stone building, which " +
        "appears to be the local prison. Open doorways lead " +
        "south and east deeper into the prison, while the " +
        "street is back to the west. The walls are the " +
        "same, heavy stone as other buildings are built " +
        "from, but seem older somehow. Perhaps this was one " +
        "of the first buildings in the village. Whatever " +
        "its original purpose, it now houses the main garrison " +
        "of the village guard, as well as the occasional " +
        "prisoner.\n");

    add_item(({"floor", "ground"}),
        "The floor of the room is simply hard-packed " +
        "earth.\n");
    add_item(({"walls", "wall"}),
        "The walls of the room are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");

    INSIDE;

    add_exit(ROOM + "jail_corridor_1", "east");
    add_exit(ROOM + "jail_garrison", "south");
    add_exit(ROOM + "road_17_2", "west");

    reset_room();
}
