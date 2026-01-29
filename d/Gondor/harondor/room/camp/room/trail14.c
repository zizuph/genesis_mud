/* Name      : /d/Gondor/harondor/room/camp/room/trail14.c
 * Purpose   : A trail leading to a camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-14
 * Modified  : Sir Toby, Gondor Domain, 2006-07-27
 *                       Updated with update_pebbles()
 *             2006.08.27, fixed typo. Toby
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
//#include  "local.h"

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/room/camp/base_trail.c";

#define HAR_RM_CAMP_DIR HAR_RM_DIR + "camp/room/"


public void
create_area_room()
{
    FIXEUID;
    set_areatype(0);
    set_areadesc("arid land");
    set_area("southern");
    set_areaname("Gondor");
    set_land("Harondor");
    set_extraline("Dried grass grow in scattered patches across the " +
        "land. Sand has blown up over them, creating small mounds. The " +
        "trail winds between them as it runs west and east.");

    add_harad_trail_tells();
    add_desert();
    add_road();
    add_trail();
    add_ephel_duath("north"); /* where they are in relation to the trail */

    add_exit(HAR_RM_CAMP_DIR + "trail15", "east",0,1,1);
    add_exit(HAR_RM_CAMP_DIR + "trail13", "west",0,1,1);

    set_trail_herbs();
    
    reset_room();
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


void
reset_room()
{
   update_pebbles();
}

