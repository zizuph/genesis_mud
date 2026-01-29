/*
 *	/d/Gondor/harondor/room/road04s.c
 *  
 *
 *  Modification log:
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
    set_area("barren");
    set_areaname("southern Gondor");
    set_land("Harondor");
    set_extraline("Thin grasses grow alongside the road. They are dried " +
        "and brown, and grow in clumps in the sand.");

    add_desert();
    add_road();
    add_ephel_duath("northeast"); /* where they are in relation to the road */
    
    add_exit(HAR_RM_DIR + "road04s", "north");
    add_exit(HAR_RM_DIR + "road06s", "south");
    
}
