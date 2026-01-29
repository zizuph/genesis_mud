/* Name      : /d/Gondor/harondor/room/camp/room/camp07.c
 * Purpose   : The camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2005-11-21
 * Modified  : Sir Toby, Gondor Domain, 2006-02-28
 *                       Modified NPC path and pavilion desc.
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

public string enter_pavilion();

object	*Haradrim = allocate(6);

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
        "in scattered patches. Looking in all directions sand has " +
        "blown up over them, creating mounds in different sizes, " +
        "this part of the apparent camp the ground is kept clean of " +
        "any mounds. Looking south there is a very large tent raised, " +
        "with a pavilion built just to the right of it.");

    add_harad_camp_tells();
    add_desert();
    add_large_pavilion();
    add_tall_tents();
    add_animal_pens();
    add_ephel_duath("north"); /* where they are in relation to the camp */

    add_exit(HAR_RM_CAMP_DIR + "camp07", "north");
    
    set_tent_path(HAR_RM_CAMP_DIR + "camptentchief");

    /* A time check will tell wether or not the chief is in 
       the pavilion or tent. */

	add_cmd_item( ({ "pavilion", "large pavilion", }), "enter", enter_pavilion);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(Haradrim, 1);
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

public string
enter_pavilion()
{
    if (!check_allow())
    {
        ENV(TP)->set_dircmd("pavilion");
        write("You step into the large pavilion next to the large tent.\n");
        TP->move_living("into the large pavilion", HAR_RM_CAMP_DIR + "pavilion.c");
    }
   return "";
}

/* Masking this to always allow entry. Should I keep it like that for the quest support?
 * Since the guard NPC are so much tougher, the chance of sneaking in is almost reduced
 * and if a player finds the backdoor in, he or she should be rewarded with less 
 * fighting to reach the quest since the chief would assume all is in order then.
 */
public int
check_allow()
{
   return 0;
}