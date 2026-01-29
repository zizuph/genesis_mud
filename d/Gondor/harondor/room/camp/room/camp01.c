/* Name      : /d/Gondor/harondor/room/camp/room/camp01.c
 * Purpose   : The camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-25
 *
 * Modified  : 2006-02-28, Sir Toby
 *                         Added cloning support.
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/room/camp/base_camp.c";

object	*Haradrim = allocate(4);

public void
create_camp()
{
    FIXEUID;
    set_areatype(0);
    set_areadesc("arid land");
    set_area("southern");
    set_areaname("Gondor");
    set_land("Harondor");
    set_extraline("Across the dry and barren land dried grasses grow " +
        "in scattered patches. Sand has blown up over them, creating " +
        "mounds in different sizes. There are tents placed evenly over " +
        "the area, a few bigger then most. Northwest of you is one " +
        "particularly large with tent flaps open. Westwards there are no " +
        "tents but there is a small pavilion errected.");

    add_harad_camp_tells();
    add_desert();
    add_tall_tents();
    add_animal_pens();
    add_ephel_duath("north"); /* where they are in relation to the camp */

    add_exit(HAR_RM_CAMP_DIR + "camp09", "east", check_allow, 2);
    add_exit(HAR_RM_CAMP_DIR + "camp02", "north", check_allow, 2);
    add_exit(HAR_RM_CAMP_DIR + "campE01", "west", check_allow, 2);
    add_exit(HAR_RM_CAMP_DIR + "camp08", "south", check_allow, 2);
    
    set_tent_path(HAR_RM_CAMP_DIR + "camptent01");

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(Haradrim, 0);
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


