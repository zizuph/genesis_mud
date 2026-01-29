inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_BASE_DIR + "girdley/isle2","west",0,1
#define EXIT2 ER_BASE_DIR + "girdley/isle4","south",0,1


void
create_er_room()
{

    area = "in the middle of";
    areaname = "Girdley Island";
    land = "the Shire";
    areatype = 7;
    areadesc = "freshly-cut path";
    grass = "green";
    treetype = "small";

    extraline = "The path that leads this way from the south here "+
    "curves to the west, making a semi-circle. The trees are not "+
    "cleared here and the path is fairly narrow, though not overgrown "+
    "as it has been recently cleared. Bushes grow scattered among the " +
    "trees and the path leads south and west.";

    add_item(({"path","narrow path"}),
      "The path has been recently made, seemingly cut from the youngest and "+
      "smallest growth, as it meanders greatly through the trees.\n");
    add_item(({"bushes", "bush", "shrubs", "shrub"}),
        "Bushes and shrubs grow scattered around the island. They're tall " +
        "and block your view beyond the river, and very thorny. " +
        "@@ranger_descr@@\n");
    add_item(({"thorny bushes", "thorny bush"}),
        "These tall bushes are covered with thorns. They look dangerous " +
        "and immpossible to get through without hurting yourself.\n");
    add_item(({"thorns"}),
        "The thorns on the bushes are about a finger's length and very " +
        "sharp. They grow all over the thorny bushes and are dangerous " +
        "looking.\n");
    add_item(({"tall bushes", "tall bush"}),
        "The tall bushes grow along the edge of the island. They are " +
        "thick and block your view of the shore beyond.\n");
    add_item(({"faint path"}),
        "@@faint_path_descr@@\n");

    

    add_exit(EXIT1);
    add_exit(EXIT2);
     set_up_herbs( ({   GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "daffodil", 
                        SHIRE_HERB_DIR  + "calendula",
                        GONDOR_HERB_DIR + "carrot_wild",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
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
void find_entrance()
{

    write("You carefully enter the bushes and disappear.\n");
    TP->move_living("M",GIRD_DIR + "secret01",1);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from the southwest.\n",TP);
}


// defines the action
int enter_bushes(string str)
{

    if (R_ALLOWED)
    {    
        if(!str)
        {
            write("Enter what? \n");
            return 1;
        }

        if(str =="bushes" || str == "bush" || str == "shrub" || 
           str == "shrubs" || str == "thorny bushes" || str == "thorny bush")
        {
            find_entrance();
            return 1;
        }
        else 
        {
            write("Enter bushes?\n");
            return 1;
        }
    }
    
}


// lets rangers see it in general
string ranger_descr()
{
    if (R_ALLOWED)

        return "Looking closer, you see where the bushes have been " +
            "parted. A very faint path leads into the bushes.";
    else
        return "";

}

// lets them see it in detail. tree_top_descr() shows up in the tree
string faint_path_descr()
{
    if (R_ALLOWED)
    
        return "This path is barely visible but leads into the bushes. " +
            "Only the very skilled are able to see it.";
    else
        return "You find no faint path.";

}
