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

    set_extraline("Insects buzz in clouds around you then settle down " +
        "on the pools of water and hillocks. The marsh stretches surrounds " +
        "you and is dotted with dead trees. To the south, the Great East " +
        "road bends around the marsh.");

     set_up_herbs( ({   GONDOR_HERB_DIR + "bpotato",
                        GONDOR_HERB_DIR + "morgurth",
                        SHIRE_HERB_DIR  + "adillyp", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        KRYNN_HERB_DIR + "cattail",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);

    add_exit(ER_DIR + "erb14n2", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb15n1", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n2", "west", 0, "@@move_hard@@");
}

