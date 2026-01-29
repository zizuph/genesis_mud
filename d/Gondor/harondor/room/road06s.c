/*
 *	/d/Gondor/harondor/room/road06s.c
 *  The Harad road
 *  -- Finwe, July 2005
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
//#include  "local.h"

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
    set_extraline("The road runs in a north and south and passes by a ruined " +
        "watchtower. Dried grasses grow around the fallen stone blocks, " +
        "many of which are buried in the sand.");

    add_harad_road_tells();
    add_desert();
    add_road();
    add_ephel_duath("northeast"); /* where they are in relation to the road */

    add_item(({"watchtower", "tower"}),
        "It is a pile of broken stones alongside the road. It was probably " +
        "a lookout station built centuries ago. Now, there is little that " +
        "remains beyond an outline of stones buried in the sand.\n");
    add_item(({"outline"}),
        "It is made up of broken stones buried in the ground.\n");
    add_item(({"broken stones", "broken rocks"}),
        "They lay toppled over on the ground and on top of each other. " +
        "They are cracked and broken, and look weather beaten.\n");
    
    add_exit(HAR_RM_DIR + "road05s", "north");
    add_exit(HAR_RM_DIR + "road07s", "south");
    
}

