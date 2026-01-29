/*
 * This is part of a road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include <macros.h>
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
            guards[i]->set_team_name("gate_team");
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
    return "south";
}

public int
block_me()
{
    return 0;
    write("A guard approaches you and warns you off, " +
        "stating a wyvern has been seen at the edges of " +
        "the forest across the fields outside of the " +
        "village and nobody is allowed in or out for now.\n");
    return 1;
}

public void
create_road()
{
    set_short("wide dirt intersection");
    set_long("   You are on a wide dirt intersection at the " +
        "northern edge of Port Macdunn. A wide dirt road " +
        "leads south from here through the center of the " +
        "village, and a narrower one leads westwards along " +
        "the northern edge. Earthen embankments surround " +
        "the intersection on the northern and eastern " +
        "sides, through which wide roads pass through " +
        "open gates.\n");

    add_exit("/d/Khalakhor/se_speir/plains/room/plains_15_8", "north",
        VBFC_ME("block_me"));
    add_exit("/d/Khalakhor/se_speir/plains/room/plains_16_9", "east",
        VBFC_ME("block_me"));
    add_exit(ROOM + "road_12_2", "south");
    add_exit(ROOM + "road_11_1", "west");
    reset_room();
}
