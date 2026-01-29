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

    set_extraline("The ground is a little drier here than elsewhere in " +
        "the marsh. The swamp stretches in all directions. A multitude of " +
        "insects fly around then settle on the the water and ground.");

     set_up_herbs( ({   GONDOR_HERB_DIR + "coccinea",
                        GONDOR_HERB_DIR + "angurth",
                        SHIRE_HERB_DIR  + "adillyp", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        GONDOR_HERB_DIR + "seregon",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);

    add_exit(ER_DIR + "erb9n2", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb11n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb10n1", "south", 0, "@@move_hard@@");
}
