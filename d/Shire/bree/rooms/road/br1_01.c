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

    areadesc = "field";
    area = "hidden by";
    areaname = "tall grass";
    land = "the Shire";
    areatype = 1;
    grass = "green";
    treetype = "small";

    extraline = "Bushes line the road and grow in groups across the " +
        "wide field. An occasional tree can be seen in the distance, and " +
        "boulders dot the land. Wildflowers wave in the breeze. ";

    add_item(({"path"}),
        "This thin line meanders west through the brush and trees. It is little " +
        "used and probably forgotten.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow in scattered groups. They are scrawny looking, " +
        "and of different sizes. Some bushes grow to the southwest, " +
        "obscuring the path. On the other side of the bushes you see " +
        "@@road_desc@@\n");
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
    
    

    set_up_herbs( ({    GONDOR_HERB_DIR + "suranie",
                        GONDOR_HERB_DIR + "tuo",
                        SHIRE_HERB_DIR  + "huckleberry", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"field","ground","trees","flowers","path","track"}), 3);

    add_exit(ROAD_DIR + "br1_02", "west");

}

public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");

}

int enter_bushes(string str)
{
    if(str =="bushes" || str == "path")
    {
        write("You enter the bushes and disappear.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " disappears into the bushes.\n",TP);
        TP->move_living("M",ROAD_DIR + "nroad04", 1);
        return 1;
    }
    else 
    {
        write("Enter what, the bushes??\n");
        return 1;
    }
    
}

string road_desc()
{
    object other_room;
    mixed opeople;
    string views;

    if (!LOAD_ERR(OTHERSIDE))
        other_room = find_object(OTHERSIDE);
    else
        return "Error with view. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "no one on the old highway.";
    else
        return COMPOSITE_LIVE(opeople)+" is standing on the old highway.";

}
