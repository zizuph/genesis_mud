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

    set_extraline("A strong odor rises from the swamp. Dead trees poke " +
        "out of the water. The swamp looks treacherous with some hillocks " +
        "floating nearby, and brackish water laps at your feet.");

     set_up_herbs( ({   GONDOR_HERB_DIR + "morgurth",
                        KALAD_HERB_DIR  + "fungari",
                        SHIRE_HERB_DIR  + "chives", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        GONDOR_HERB_DIR + "ginger",
                        
                        }),
                  ({"water","ground","trees","flowers","path","track", "pool"}), 3);


    add_exit(ER_DIR + "erb11n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb12n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb10n2", "west", 0, "@@move_hard@@");

}

