/*
 *	/d/Gondor/harondor/room/road04.c
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
    set_extraline("The land is dry and arid. Sand and rocks cover the " +
        "area, and stretch in all directions. A range of mountains " +
        "stand in the distance to the northeast. The road runs northeast " +
        "and south.");

    add_desert();
    add_road();
    add_ephel_duath("northeast"); /* where they are in relation to the road */
    
    add_exit(HAR_RM_DIR + "road03s", "northeast");
    add_exit(HAR_RM_DIR + "road05s", "south");
}
