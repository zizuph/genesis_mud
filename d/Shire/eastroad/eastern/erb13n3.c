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

    set_extraline("The marsh stretches in all directions and is dotted " +
        "with dead trees. They are on the hillocks and poke out of the " +
        "brackish water.");

     set_up_herbs( ({   GONDOR_HERB_DIR + "myrtle",
                        GONDOR_HERB_DIR + "hemlock",
                        SHIRE_HERB_DIR  + "adillyp", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        GONDOR_HERB_DIR + "seregon",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);


    add_exit(ER_DIR + "erb13n2", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14n3", "northeast", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb12n2", "west", 0, "@@move_hard@@");
}

