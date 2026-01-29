/* Name      : /d/Gondor/harondor/room/camp/room/camp06.c
 * Purpose   : The camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-20
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
//#include  "local.h"

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/room/camp/base_camp.c";

object	*Haradrim = allocate(2);

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
        "the area, a few bigger then most. Just east of you is one " +
        "such large tent with its flaps open.");

    add_harad_camp_tells();
    add_desert();
    add_tall_tents();
    add_animal_pens();
    add_ephel_duath("north"); /* where they are in relation to the camp */

    add_exit(HAR_RM_CAMP_DIR + "s09", "south","@@my_block",3,1);
    add_exit(HAR_RM_CAMP_DIR + "camp05", "north", check_allow, 2);
    add_exit(HAR_RM_CAMP_DIR + "camp07", "west", check_allow, 2);
    
    set_tent_path(HAR_RM_CAMP_DIR + "camptent06");

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


int my_block()
{
    if(check_allow())
       return 1;

    return wind_block("east");
}

