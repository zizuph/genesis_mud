/*
 * jail_garrison.c
 *
 * Main 'home' of the village guards of Port MacDunn.
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
        guards = allocate(5);

    for (i = 0; i < sizeof(guards); i++)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(NPC + "guard");
        
            if (i == 0)
                guards[i]->set_team_leader();
            else
                guards[i]->set_team_follower();
            guards[i]->set_team_name("garrison_team");
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
    set_short("guard garrison of Port Macdunn");
    set_long("   You are in the living quarters of the main " +
        "garrison for the village guard of Port Macdunn. " +
        "The living quarters are rather spartan, cots and " +
        "chests mainly. No decorations of any kind adorn " +
        "the stone walls or dirt floor. Despite the rather " +
        "simple living conditions, the room is extremely " +
        "well ordered, and as clean as you could expect with " +
        "a dirt floor. These troops might not be highly " +
        "skilled, but they are well disciplined.\n");

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
    add_item(({"cot", "cots"}),
        "The cots are simply constructed. Ample for sleeping " +
        "on, but neither incredibly comfortable nor expensive.\n");
    add_item(({"chest", "chests"}),
        "The chests are simple wooden construction, banded " +
        "with iron straps, and securely locked.\n");

    INSIDE;

    add_exit(ROOM + "jail", "north");

    reset_room();
}
