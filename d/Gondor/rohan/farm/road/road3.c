/*
 *      /d/Gondor/rohan/farm/road/road3.c
 *
 *      Coded 1992 by Olorin
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance to area_room.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Scout;

public void
reset_room()
{
    ::reset_room();

    Scout = clone_npc(Scout, NPC_DIR + "farm/dunscout");
}

public void
create_area_room() 
{
    set_areadesc("farm road");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_treetype("oak");
    set_extraline("You are now in a narrow valley in the White Mountains. The "
      + "small farm road continues to the northwest. To the south, you "
      + "can make out some buildings. The trees seem to grow thinner there.");
    add_exit(FARM_DIR + "road/road2", "northwest", 0, 1);
    add_exit(FARM_DIR + "road/yard1", "south", 0, 1);
 
    reset_room();
}

