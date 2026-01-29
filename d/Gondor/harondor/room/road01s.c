/*
 *	/d/Gondor/harondor/room/road01.c
 *  This file is a base file for the harad road

 *
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
    set_extraline("The road runs north and south, passing through the " +
        "wastelands of Harondor. It is ancient looking and dusty, but still " +
        "appears well used. North is a bridge that passes over the river Poros.\n");

    add_item(({"poros", "river poros", "poros river", "river"}),
        "The river Poros lies nortth of the road. It cuts across the " +
        "land, from the northeast to the southwest. It marks the southern " +
        "boundary of Ithilien.\n");
    add_item(({"ithilien"}),
        "It is the land north of here, on the other side of the river.\n");
    add_desert();
    add_road();
    add_ephel_duath("east"); /* where they are in relation to the road */
    
    add_exit(HAR_RM_DIR + "bridge01", "north");
    add_exit(HAR_RM_DIR + "road02s", "south");
    
}
