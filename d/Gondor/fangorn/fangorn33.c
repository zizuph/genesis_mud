/*
 *	/d/Gondor/fangorn/fangorn33.c
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

public int   check_huorn();


public void
create_area_room()
{
    string *herbs = HERB_MASTER->query_herbs("forest");

    add_exit(FANGORN_DIR + "fangorn28", "northwest", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangorn29", "northeast", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangorndd", "north", test_loc, 2, 1);

    add_exit("/d/Gondor/rohan/plains/l08", "south", check_huorn, 2, 1);

    set_areatype(7);
    set_areadesc("edge");
    set_area("southeastern");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("thick, tall");
    set_treetype("ancient spruce");
    set_forest_density(10);
    set_extraline("The trees here are relatively thin. Just south of here, "
        + "a small trail leads out of the forest onto the Rohan plains. The "
        + "ancient trees do not seem inviting. A small stream flows in "
        + "from the northwest.");

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
 
    set_up_herbs( ({ HERB_DIR + "suranie", HERB_DIR + "foxglove", }),
		  ({ "ground", "forest", }), 3);
}

public void
init()
{
    ::init();
    init_drink();
}

public int
check_huorn()
{
    switch (TP->query_race())
    {
    case "huorn":
        return 1;
	       break;
    case "ent":
        return 1;
        break;
    default:
	       write("With a sigh of relief, you leave Fangorn forest behind.\n");
	       return 0;
	       break;
    }
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


