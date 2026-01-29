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

    set_extraline("The marsh stretches out to the north as far as you " +
        "can see. It is bordered by the Great East road that runs around " +
        "it and is visible to the south.");
    
     set_up_herbs( ({   GONDOR_HERB_DIR + "coccinea",
                        GONDOR_HERB_DIR + "morgurth",
                        SHIRE_HERB_DIR  + "calendula", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        GONDOR_HERB_DIR + "blueberry",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);


    add_exit(ER_DIR + "erb13n2", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13", "south", 0, "@@move_med@@");

}

