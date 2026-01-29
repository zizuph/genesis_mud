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

#define ROAD_DIR    "/d/Shire/bree/rooms/road/"
void
create_er_room()
{

    areadesc = "ravine";
    area = "cutting through";
    areaname = "the tall grass";
    land = "the Shire";
    areatype = 5;
    grass = "green";
    treetype = "small";

    extraline = "The ravine runs east and southwest through the " +
        "tall grass. This old riverbed is deep enough to hide you and " +
        "surrounded by bushes and trees. Tall bushes block your way to the " +
        "east.";

    add_item(({"path"}),
        "The path is not visible in the ravine. \n");
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
    add_item(({"ancient trees", "old trees", "tall trees"}),
        "These trees are very old and very tall. Their size suggests that " +
        "they have been growing here for countless years and were probably " +
        "part of a forest that was once here.\n");
    add_item(({"short trees", "small trees"}),
        "They are shorter than the ancient trees as they are younger. These " +
        "trees look as if they have recently begun to grow, and are not " +
        "very tall yet.\n");
    add_item(({"ravine", "shallow ravine"}),
        "The ravine runs north and is not very deep. It appears to have " +
        "been a stream bed many years ago. The bottom is covered with many " +
        "stones, polished when a water ran through it.\n");
    add_item(({"stones", "polished stones"}),
        "Many stones cover the bottom of the ravine. They are rounded " +
        "and polished smooth by water that once ran through this ravine.\n");

    set_up_herbs( ({    GONDOR_HERB_DIR + "astaldo",
                        GONDOR_HERB_DIR + "handasse",
                        SHIRE_HERB_DIR  + "bilberry", 
                        SHIRE_HERB_DIR  + "glimmer",
                        GONDOR_HERB_DIR + "hemlock",
                        
                        }),
                  ({"ground","riverbank","ravine","rocks","stones"}), 3);

    add_exit(GIRD_DIR + "secret05", "southwest");

}

init()
{
    ::init();
    add_action("enter_bushes", "enter");
}

// moves them there secretly
int enter_bushes(string str)
{
    if(str =="bushes" || str == "shrubs")
    {
        write("You carefully enter the bushes and disappear.\n");
        say(QCTNAME(TP) + " enters the bushes and disappears.\n");
        TP->move_living("M", ROAD_DIR + "nroad07",1);
        return 1;
    }

    else 
    {
        write("Enter the bushes?\n");
        return 1;
    }

}

