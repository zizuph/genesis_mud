/* Name      : /d/Gondor/harondor/room/camp/room/s03.c
 * Purpose   : A secret trail around the camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-17
 * Modified  : 
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
//#include  "local.h"

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/room/camp/base_trail.c";

public void
create_area_room()
{
    FIXEUID;
    set_areatype(0);
    set_areadesc("arid land");
    set_area("southern");
    set_areaname("Gondor");
    set_land("Harondor");
    set_extraline("Across the dry and barren land dried grasses grow " +
        "in scattered patches. Sand has blown up over them, creating " +
        "mounds in different sizes. Looking northwards the " +
        "mounds looks smaller though.");

    add_harad_secret_tells();
    add_desert();
    add_road();
    add_trail();
    add_ephel_duath("north"); /* where they are in relation to the trail */

    add_exit(HAR_RM_CAMP_DIR + "trail10", "northwest",0,1,1);
    add_exit(HAR_RM_CAMP_DIR + "s01", "north",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s02", "west",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s05", "south",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s04", "east",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s06", "southeast",0,2,1);
    add_exit("", "northeast","@@s_block",1,1);
    add_exit("", "southwest","@@s_block",1,1);

    set_trail_herbs();
    
}

public void
init()
{
    ::init();
 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
