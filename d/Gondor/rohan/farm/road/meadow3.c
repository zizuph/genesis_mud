/* This file is /d/Gondor/rohan/farm/road/meadow3.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

object *wolf = allocate(1 + random(3));

public void
create_area_room() 
{
    set_areadesc("meadow");
    set_areatype(3);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green");
    set_treetype("birch");
    add_exit(FARM_DIR + "road/yard1", "northwest", 0);

    set_up_herbs( ({ SHIRE_HERB_DIR + "parsley", HERB_DIR + "attanar",
                     HERB_DIR + "savory", HERB_DIR + "ungolestel", }),
                  ({"bushes","meadow","forest","path","here"}), 4);
    reset_room();
}

static void
clone_wolf(int n)
{
    int     i;

    for (i = 0; i < sizeof(wolf); i++)
        if (!objectp(wolf[i]))
        {
            wolf[i] = clone_object(NPC_DIR + "wolf");
            wolf[i]->set_restrain_path(FARM_DIR + "road");
            wolf[i]->move_living("down", TO);
            set_alarm(15.0 + rnd() * 30.0, 0.0, clone_wolf);
            return;
        }
}

public void
reset_room()
{
    ::reset_room();

    set_alarm(4.0, 0.0, clone_wolf);
}

