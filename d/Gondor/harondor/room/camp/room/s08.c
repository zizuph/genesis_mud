/* Name      : /d/Gondor/harondor/room/camp/room/s08.c
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
        "mounds in different sizes.");

    add_harad_secret_tells();
    add_desert();
    add_road();
    add_trail();
    add_ephel_duath("north"); /* where they are in relation to the trail */

    add_exit(HAR_RM_CAMP_DIR + "s07", "west",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s09", "north",0,2,1);
    add_exit(HAR_RM_CAMP_DIR + "s11", "east","@@my_east",6,1);
    add_exit("", "northwest","@@s_block",1,1);
    add_exit("", "northeast","@@s_block",1,1);
    add_exit("", "southeast","@@s_block",1,1);
    add_exit("", "south","@@s_block",1,1);
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

int my_east()
{
    write("With difficulty you walk east over the mounds.\n");
    return 0;
}