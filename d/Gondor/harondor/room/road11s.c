/*
 *	/d/Gondor/harondor/room/road06s.c
 *  The Harad road
 *  -- Finwe, July 2005
 * 
 *  Modification history:
 *     -- Palmer, Aug 2006: Worked on long description
 *     -- Toby, Aug 2006: Fixed typos and made a exit check description
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/harondor/base_road.c";

public void
create_area_room()
{
    FIXEUID;
    set_areatype(0);
    set_areadesc("arid land");
    set_area("southern");
    set_areaname("Gondor");
    set_land("Harondor");
    set_extraline("The arid, dry land is hot. Thin grasses grow along " +
        "the road and in clumps in the sand. Sand blows across the road, " +
        "obscuring most of it from view. To the south is an old bridge " +
        "in need of repair, crossing a mighty river. There is a crew of " +
        "Haradrim repairing the bridge and another guarding for trespassers, " +
        "most probably making it impossible to cross.");

    add_harad_road_tells();
    add_desert();
    add_road();
    add_ephel_duath("north"); /* where they are in relation to the road */

    add_item(({"bridge"}),
        "It is old and made of wood and spans the river south of here. " +
        "Its being repaired by a crew of Haradrim.\n");
    add_item(({"crew", "haradrim"}),
        "The Haradrim crew are working on the bridge.\n");
    add_item(({"river", "harnen river", "harnen"}),
        "The river runs west through the land.\n");

    add_exit(HAR_RM_DIR + "road10s", "north");
    add_exit(HAR_RM_DIR + "road12s", "south", "@@check_open");
}


/* Function name: check_open
 * Description  : Gets called from this room.
 * Arguments    : none
 * Returns      : int 1/0 - closed/open
 *
 * Comment      : Area south will remain closed until further
 *                development have been completed in Harondor.
 *                                           - Toby
 */
int check_open()
{
   write("As you approach the broken down bridge a group of Haradrim closes on you with not " +
         "too friendly a look in their eyes. They block your attempt of crossing the river.\n");
   say(QCTNAME(TP) + " tries to approach the bridge in a botched attempt to cross, but alas, " +
                    "big group of Haradrim intercept and block the way.\n");
      
   return 1;
}

