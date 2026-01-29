/*
 *	/d/Gondor/harondor/room/road06s.c
 *  The Harad road
 *  -- Finwe, July 2005
 *
 *     -- Modification history: 
 *        
 *        - 2005-11-13, Sir Toby: Added a non-obvious exit and 
 *                                added to room description to make
 *                                the trail discoverable.
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
    set_extraline("Dried grasses grow in scattered patches across the " +
        "land. Sand has blown up over them, creating small mounds. There " +
        "is a small trail leading off the road to the northeast and the " +
        "road cuts through the mounds as it runs north and south.");

    add_harad_road_tells();
    add_desert();
    add_road();
    add_ephel_duath("north"); /* where they are in relation to the road */

        /* Added by Toby to fit the new room description  */
    add_item(({"trail", "small trail"}),"A small trail that leads away off " +
               "the main road towards the northeast.\n"); 
    
    add_exit(HAR_RM_DIR + "road07s", "northwest");
    add_exit(HAR_RM_DIR + "road09s", "south");
    add_exit(HAR_RM_DIR + "camp/room/trail01", "northeast",0,1,1);
    
}

