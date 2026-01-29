/*
 *	/d/Gondor/fangorn/fangorn23.c
 *
 *	A room in Fangorn forest
 *
 * Alto, 12 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";
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

    add_exit(FANGORN_DIR + "fangorn19", "south", test_loc, 2, 1);

    set_areatype(7);
    set_areadesc("tangled thicket");
    set_area("central");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("brown, dead");
    set_treetype("ancient hickory");
    set_forest_density(40);
    set_extraline("The trees here must be the oldest in the forest. They "
        + "seem cloaked in darkness and wave their limbs threatenly above "
        + "you, although you can detect no breeze. A small stream flows "
        + "in from the northwest.");

    set_drink_from("stream");

    add_prop(OBJ_I_CONTAIN_WATER, -1);


    add_item(({"water", "stream"}), "The small stream runs past, with "
        + "little noise, on its way east. The water looks cool and "
        + "inviting.\n");

    /* add the common room items for Fangorn forest */

    add_fangorn_items();    


    /* add the common tells for Fangorn forest */

    set_tell_time(120);

    add_fangorn_tells();
 
    set_up_herbs( ({ HERB_DIR + "curugwath", HERB_DIR + "attanar", }),
		  ({ "ground", "forest", }), 3);
}

public void
init()
{
    ::init();
    init_drink();
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


