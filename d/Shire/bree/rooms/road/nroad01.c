/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * Modified:
 *
 *  2008-05-02, Toby: Added     set_dircmd("bushes");
 *  Jan 2019: Finwe, Added treetop fort description
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include <composite.h>
#include <filter_funs.h>

inherit ROAD_BASE;

#define NEED_CLIMB_SKILL    30
#define TREETOP "/d/Shire/bree/rooms/road/treetop"

/* moved to defs.h */
//#define R_ALLOWED   IS_RANGER(TP) || IS_SHIRE_WIZARD(TP) || IS_GONDOR_WIZARD (TP)

void
create_road_room()
{
    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("The highway appears abandoned as weeds and grass " +
        "grow on the road. It is dark and gloomy, and probably " +
        "hasn't been used in many long years. Tall and ancient trees " +
        "grow on either side of the highway. Bushes grow on either side " +
        "of the highway and around the trees.\n");

    add_item(({"ancient trees"}),
        "The ancient trees that originally grow here look like they were " +
        "planted ages ago and survived many battles. They are larger than " +
        "the tall trees. Scars and gashes can be seen in the trunks of " +
        "the trees. @@ranger_descr@@\n");
    add_item(({"scars", "gashes"}),
        "The gashs and scars in the trees are deep, left over from battles " +
        "that were fought here.\n");
    add_item("tree",
        "There are tall, large, and ancient trees growing around here.\n");
    add_item("large tree",
        "@@ancient_tree_descr@@");
    add_item(({"bushes"}),
        "They are tall and overgrown, and grow alongside the road and under the trees. @@bushes_descr@@\n");

    set_add_nroad();

    add_exit(ROAD_DIR + "nroad02",   "north","@@tree_north@@");
    add_exit(ROAD_DIR + "crossroad", "south","@@tree_south@@");
}

public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");
}

string bushes_descr(string str)
{
        if (R_ALLOWED || this_player()->query_wiz_level())
            return " Hidden within the bushes is a way so that you may " +
                "enter them and go behind the trees.";
        else
            return "";


}

// moves them there secretly
void find_entrance()
{

    write("You disappear off the road and into the bushes.\n");
    set_dircmd("bushes");
    TP->move_living("M",ROAD_DIR + "treetop_glade");
    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went east into the bushes.\n");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from the road.\n",TP);
}


int enter_bushes(string str)
{

    if (R_ALLOWED || this_player()->query_wiz_level())
    {    
        if(!str)
        {
            write("Enter what?\n");
            return 1;
        }

        if(str =="bushes")
        {
            find_entrance();
            return 1;
        }
        else 
        {
            write("Enter what?\n");
            return 1;
        }
    }    
}


string ranger_descr()
{
    if (R_ALLOWED || this_player()->query_wiz_level())

        return "One tree near the road looks larger than the others. Bushes " +
            "grow around it, hiding a way behind the tree.";
    else
        return "";

}


string
tree_top_descr()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(TREETOP))
        other_room = find_object(TREETOP);
    else
        return "Some sort of magic is plaguing the treetop. Contact " +
            "a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return " No one is visible in the large tree.";
    else
        return " Up in the tree, you see hidden "+COMPOSITE_LIVE(opeople)+
            " watching your every move.";
}

string ancient_tree_descr()
{
    if (R_ALLOWED || this_player()->query_wiz_level())
    
        return "This tree blends in with the other ancient trees, growing " +
            "away from the road." + tree_top_descr() + "\n";
    else
        return "You find no ancient tree.\n";
}

void tree_north()
{
    tell_tree("went north along the ancient highway..");
    tell_tree_fort("went north along the ancient highway.\n");
}

void tree_south()
{
    tell_tree("went south to the Crossroads.");
    tell_tree_fort("went south to the Crossroads.\n");

}
