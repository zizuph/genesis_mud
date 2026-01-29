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
#include <composite.h>
#include <filter_funs.h>


#define OTHERSIDE   "/d/Shire/bree/rooms/road/nroad04"

void create_er_room()
{

    areadesc = "abandoned path";
    area = "hidden by";
    areaname = "tall grass";
    land = "the Shire";
    areatype = 1;
    grass = "green";
    treetype = "small";

    extraline = "The path leads northwest into the grass and disappears. " +
        "The grass is green and tall, and dotted with wildflowers and trees.";

    add_item(({"path"}),
        "This thin line meanders through the brush and trees. It looks " +
        "little used as it disappears into the grass.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow in scattered groups. They are scrawny looking, " +
        "and of different sizes. Some bushes grow to the southwest, " +
        "obscuring the path.\n");
    add_item(({"tall grasses", "grasses", "grass"}),
        "The grasses are dark green and wave in the wind. They hide " +
        "everything except for the bushes and trees that grow around here.\n");
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
    add_item(({"rocks"}),
        "They are all sizes and scattered across the ground. Most of them " +
        "are jagged and half buried in the ground.\n");
    add_item(({"boulders"}),
        "The boulders are very large and partially buried in the ground. " +
        "Grasses and bushes grow around them. Some are tall and angular " +
        "and others are rounded and wide.\n");
    
    add_prop(ROOM_M_NO_SCRY,1);
    

    set_up_herbs( ({    GONDOR_HERB_DIR + "suranie",
                        GONDOR_HERB_DIR + "tuo",
                        SHIRE_HERB_DIR  + "huckleberry", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"field","ground","trees","flowers","path","track"}), 3);

    add_exit(ROAD_DIR + "br1_03", "northwest");
    add_exit(ROAD_DIR + "treetop_glade", "south");
    


}

