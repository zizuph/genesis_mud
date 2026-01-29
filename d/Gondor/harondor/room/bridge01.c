/*
 *	/d/Gondor/harondor/room/bridge01.c
 *  
 *  The bridge was created 2006.08.24 to allow access to
 *  the new area.
 *
 *    -- Toby
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
    set_extraline("The road runs north and south. South passing through the " +
        "wastelands of Harondor, north it lead into Ithilien. Right here " +
        "the road pass over the river Poros. The bridge you stand upon is " +
        "constructed of stoneblocks in various sizes and under it are two " +
        "huge domes to support the heavy bridge.");

    add_item(({"poros", "river poros", "poros river", "river"}),
        "The river Poros lies beneath the bridge. It cuts across the " +
        "land, from the northeast to the southwest. It marks the southern " +
        "boundary of Ithilien.\n");
    add_item(({"ithilien"}),
        "It is the land north of here, on the other side of the river.\n");
    add_item(({"bridge", "large bridge", "stone bridge", "large stone bridge"}),
        "It is a rather large bride made of stoneblocks in various sizes.\n");
    add_item(({"dome", "domes", "huge dome", "huge domes"}),
        "The domes are the base construction of the bridge, supporting its massive weight.\n");

    add_desert();
    add_road();
    add_ephel_duath("east"); /* where they are in relation to the road */
    
    add_exit(HAR_RM_DIR + "road00s", "north");
    add_exit(HAR_RM_DIR + "road01s", "south");
    
}


