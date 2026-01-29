/*
 * Secret path from Girdley Island to North Bree Road
 * Designed for rangers to travel thru the area undetected
 * Finwe, May 2004
 */
inherit "/d/Shire/eastroad/std/er_base";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_er_room()
{

    areadesc = "field";
    area = "hidden by";
    areaname = "tall grass";
    land = "the Shire";
    areatype = 9;
    grass = "green";
    treetype = "small";

    extraline = "The path descends northeast into a shallow ravine. It " +
        "is lined with bushes and grasses, hiding it from casual users. " +
        "The path leads west towards the Brandywine river, northeast, and " +
        "bends southeast.";

    add_item(({"path"}),
        "This thin line meanders west through the brush and trees. It is little " +
        "used and probably forgotten. It ends at the edge of a shallow ravine " +
        "that runs north.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow in scattered groups. They are scrawny looking, " +
        "and of different sizes. Some thorny bushes grow to the southwest, " +
        "obscuring the path.\n");
    add_item(({"tall grasses", "grasses", "grass"}),
        "The grasses are dark green and wave in the wind. They hide " +
        "everything except for the bushes and trees that grow around here.\n");
    add_item(({"trees"}),
          "Many trees grow in clusters throughout the area. Some are tall " +
          "and ancient looking while others are young and small.\n");
    add_item(({"tall trees"}),
        "These trees are very old and very tall. Their size suggests that " +
        "they have been growing here for countless years and were probably " +
        "part of a forest that was once here.\n");
    add_item(({"short trees", "small trees"}),
        "They are shorter than the other trees. They look as if they " +
        "have recently begun to grow, and are not very tall yet.\n");
    add_item(({"ravine", "shallow ravine"}),
        "The ravine runs north and is not very deep. It appears to have " +
        "been a stream bed many years ago.\n");

    set_up_herbs( ({    GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "huckleberry", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    add_exit(GIRD_DIR + "secret05", "northeast");
    add_exit("/d/Shire/bree/rooms/road/br1_02", "southeast");
    add_exit(GIRD_DIR + "secret03", "west");

}
