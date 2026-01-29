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

    set_extraline("The swamp looks trecherous with its hillocks floating " +
        "in the water. The brackish water is dotted with insects skittering " +
        "across the surface, and grasses floating in the water. The Great East " +
        "road is visible in the distance to the southeast.");

     set_up_herbs( ({   KALAD_HERB_DIR + "fungari",
                        GONDOR_HERB_DIR + "tyelka",
                        SHIRE_HERB_DIR  + "adillyp", 
                        SHIRE_HERB_DIR  + "columbine",
                        GONDOR_HERB_DIR + "savory",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);

    add_exit(ER_DIR + "erb16", "southeast", 0, "@@move_med@@");
    add_exit(ER_DIR + "erb14n3", "northwest", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb15n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14n2", "west", 0, "@@move_hard@@");

}

