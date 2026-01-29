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
    set_extraline("Sand covers most of the road where it has been blown " +
        "across the wasteland. Tufts of grass grow in scattered patches. " +
        "To the north rise a range of mountains.");

    add_harad_road_tells();
    add_desert();
    add_road();
    add_ephel_duath("north"); /* where they are in relation to the road */

    
    add_exit(HAR_RM_DIR + "road06s", "north");
    add_exit(HAR_RM_DIR + "road08s", "southeast");
    
}

