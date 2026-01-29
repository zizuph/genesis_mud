#pragma save_binary
#pragma strict_types

#include "local.h"
#include "/d/Shire/common/herbs/herb_list.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("dark area");
    set_area("bogs in");
    set_areaname("the Midgewater Marshes");
    set_land("Eriador");
    set_areatype(AREATYPE_MARSH);
    set_grass("sparse gray");
    set_treetype("dead");

    set_add_marsh();
    set_add_sky();

    set_extraline("The marsh stretches to the north and east. It " +
        "is sickly looking with sparse growth, and dangerous to travel " +
        "through. To the south, the Great East road angles around it.");

     set_up_herbs( ({   GONDOR_HERB_DIR + "tyelka",
                        GONDOR_HERB_DIR + "hemlock",
                        SHIRE_HERB_DIR  + "adillyp", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "ginger",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);

    add_exit(ER_DIR + "erb7n2", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb7", "south", 0, "@@move_medi@@");
    add_exit(ER_DIR + "erb8n2", "east", 0, "@@move_hard@@");


}
