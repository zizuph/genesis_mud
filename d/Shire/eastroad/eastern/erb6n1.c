#pragma save_binary
#pragma strict_types

#include "local.h"
#include "/d/Shire/common/herbs/herb_list.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the wilds");
    set_land("Eriador");
    set_areatype(AREATYPE_FOREST);
//    set_areadesc("dark area");
    set_grass("lush long");
    set_treetype("oak");

    set_add_forest();
    set_add_sky();

    set_extraline("Trees tower over you, and they thin " +
        "to the east as they approach a marsh. A sickly smell drifts " +
        "in from the east. The path leads east, west, and southwest.");
    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees that grow here make up most of the " +
        "forest. They are tall and ancient looking. Their thick branches " +
        "spread out, blocking your view, and are covered with large " +
        treetype + " leaves.\n");
    add_item(({"path", "hidden path"}),
        "The path is well hidden and doesn't look well used. Leaves " +
        "and branches hide it from all but the most observant traveller.\n");

     set_up_herbs( ({   GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "hemlock",
                        SHIRE_HERB_DIR  + "daffodil",
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "basil",

                        }),
                  ({"river","ground","trees","flowers","path","track"}), 3);


//    add_std_herbs("forest");

    add_exit(ER_DIR + "erb7n2", "east", 0, "@@move_medi@@", 1);
    add_exit(ER_DIR + "erb5n1", "west", 0, "@@move_medi@@", 1);
    add_exit(ER_DIR + "erb5", "southwest", 0, "@@move_medi@@", 1);

}
