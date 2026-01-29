/*
 *	/d/Gondor/fangorn/fangorn30.c
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

public int   check_huorn();

public void
create_area_room()
{
    string *herbs = HERB_MASTER->query_herbs("forest");

    add_exit(FANGORN_DIR + "fangorn25", "northwest", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangorn26", "northeast", test_loc, 2, 1);
    add_exit(FANGORN_DIR + "fangornx", "north", test_loc, 2, 1);

    add_exit("/d/Gondor/rohan/plains/l05", "south", check_huorn, 2, 1);

    set_areatype(7);
    set_areadesc("edge");
    set_area("southwestern");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("thick, tall");
    set_treetype("ancient spruce");
    set_forest_density(10);
    set_extraline("The trees here are relatively thin. Just south of here, "
        + "a small trail leads out of the forest onto the Rohan plains. The "
        + "ancient trees do not seem inviting.");

    /* add the common room items for Fangorn forest */

    add_fangorn_items();    


    /* add the common tells for Fangorn forest */

    set_tell_time(120);

    add_fangorn_tells();
 
    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "suranie", }),
		  ({ "ground", "forest", }), 3);
}


/*
 * Function name: query_race
 * Description  : If you define different player objects for different
 *                races you should mask this function in those objects to
 *                always return the true race of the living even though
 *                query_race_name gives the current race of the living.
 *                You should nomask the redefinition of this function.
 * Returns      : string - the race name.
 */


public int
check_huorn()
{
    if (TP->query_prop("_i_killed_ent"))
    {
        write("The trees at the forest edge seem to move together to "
            + "prevent your passage.\n");
        return 1;
    }

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


