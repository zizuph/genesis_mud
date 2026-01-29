/*
 *	/d/Gondor/fangorn/fangorn13.c
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

    add_exit(FANGORN_DIR + "fangorn8", "northeast", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangorn18", "southwest", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangorn19", "southeast", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangornn", "south", test_loc, 2, 1);

    set_areatype(7);
    set_areadesc("dense stand");
    set_area("central");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("short, sparse");
    set_treetype("ancient oak");
    set_forest_density(35);
    set_extraline("The trees here look very old and aware. In all "
        + "directions you see nothing but dark, brooding forest.");

    /* add the common room items for Fangorn forest */

    add_fangorn_items();    


    /* add the common tells for Fangorn forest */

    set_tell_time(120);

    add_fangorn_tells();
 
    set_up_herbs( ({ HERB_DIR + "curugwath", HERB_DIR + "fennel", }),
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


