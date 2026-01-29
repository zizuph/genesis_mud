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

//#define EXIT1 ER_BASE_DIR + "girdley/isle2","west",0,1
//#define EXIT2 ER_BASE_DIR + "girdley/isle4","south",0,1


void
create_er_room()
{

    areadesc = "hidden path";
    area = "through a field alongside";
    areaname = "the Brandywine River";
    land = "the Shire";
    areatype = 0;
    grass = "green";
    treetype = "small";

    extraline = "The path meanders alongside the river as it passes " +
        "through bushes and small stands of trees. It runs northeast and " +
        "is barely a line from the bushes through the tall grasses.";

    add_item(({"path"}),
        "This thin line meanders through the brush and trees. It is little " +
        "used and probably forgotten.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow in scattered groups. They are scrawny looking, " +
        "and of different sizes. Some thorny bushes grow to the southwest, " +
        "obscuring the path.\n");
    add_item(({"tall grasses", "grasses"}),
        "The grasses are dark green and wave in the wind. They hide " +
        "everything except for the bushes and trees that grow around here.\n");
    add_item(({"thorny bushes", "thorny bush"}),
        "These tall bushes are covered with thorns. They look dangerous " +
        "to enter. However, the path leads through them to.\n");
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
                        SHIRE_HERB_DIR  + "daffodil", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    add_exit(GIRD_DIR + "secret02", "northeast");
}

/*
* Function name: drink_message
* Description : do the msgs for drinking from river
*/
public void
drink_message(string from)
{
    write("You drink some of the yellow water of the Brandywine river.\n"
    + "It tastes dirty and muddy.\n");
    say(QCTNAME(TP) + " drinks some water from the river.");
} 

// initializes the action
public void
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
        TP->move_living("M", GIRD_DIR + "isle3");
        return 1;
    }

    else 
    {
        write("Enter the bushes?\n");
        return 1;
    }

}
