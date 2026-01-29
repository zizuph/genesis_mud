/* Name      : /d/Gondor/harondor/room/camp/room/trail01.c
 * Purpose   : A trail leading to a camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-13
 *
 * Modified  : 2006.08.27, fixed typo. Toby
 *              
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
        "trail wind between them as it runs east and southwest towards " +
        "a road.");

    add_harad_trail_tells();
    add_desert();
    add_road();
    add_trail();
    add_ephel_duath("north"); /* where they are in relation to the road */

    add_exit(HAR_RM_CAMP_DIR + "trail02", "east");
    add_exit(HAR_RM_DIR + "road08s", "southwest");

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
