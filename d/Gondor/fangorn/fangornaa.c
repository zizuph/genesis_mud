/*
 *	/d/Gondor/fangorn/fangornaa.c
 *
 *	A room in Fangorn forest
 *
 * Alto, 12 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/minas/lib/fangorn_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define FANGORN_DIR "/d/Gondor/fangorn/"

public void
create_area_room()
{
    string *herbs = HERB_MASTER->query_herbs("forest");

    add_exit(FANGORN_DIR + "fangorn27", "north", test_loc, 2, 1);

    set_areatype(7);
    set_areadesc("edge");
    set_area("southern");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("thick, tall");
    set_treetype("ancient spruce");
    set_forest_density(10);
    set_extraline("Although the trees here are relatively thin, there "
        + "appears to be no easy trail leading out of the forest. The "
        + "ancient trees behind you do not seem inviting.");

    /* add the common room items for Fangorn forest */

    add_fangorn_items();    


    /* add the common tells for Fangorn forest */

    set_tell_time(120);

    add_fangorn_tells();
 
    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "attanar", }),
		  ({ "ground", "forest", }), 3);
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


