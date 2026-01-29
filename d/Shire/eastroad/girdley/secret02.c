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

    extraline = "The path that winds through the grass east and " +
        "southwest as it veers around some rubble. Bushes nearly conceal " +
        "the pile of broken stones half buried in the ground.";

    add_item(({"path"}),
        "This thin line meanders through the brush and trees. It is little " +
        "used and probably forgotten.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow in scattered groups. They are scrawny looking, " +
        "and of different sizes. Some thorny bushes grow to the southwest, " +
        "obscuring the path.\n");
    add_item(({"tall grasses", "grasses", "grass"}),
        "The grasses are dark green and wave in the wind. They hide " +
        "everything except for the bushes and trees that grow around here.\n");
      add_item(({"rubble"}),
        "This appears to have been a small building at one time. Little " +
        "is left of it now as it has fallen over and broken down over " +
        "the years. Trees and bushes grow in and around the rubble, " +
        "concealing it from most eyes.\n");
    add_item(({"broken stones"}),
        "These were once square blocks used in a building. They have " +
        "been broken and fell over, burying themselves in the ground.\n");
    add_item(({"trees"}),
          "Many trees grow in clusters throughout the area. Some are tall " +
          "and ancient looking while others are young and small.\n");
    add_item(({"ancient trees", "old trees", "tall trees"}),
        "These trees are very old and very tall. Their size suggests that " +
        "they have been growing here for countless years and were probably " +
        "part of a forest that was once here.\n");
    add_item(({"short trees", "small trees"}),
        "They are shorter than the ancient trees as they are younger. These " +
        "trees look as if they have recently begun to grow, and are not " +
        "very tall yet.\n");

    set_up_herbs( ({    GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "huckleberry", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    add_exit(GIRD_DIR + "secret03", "east");
    add_exit(GIRD_DIR + "secret01", "southwest");

}
