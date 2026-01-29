/*
 * Secret path for Rangers.
 * Branch 1. Runs from Bree to Weathertop
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("rolling");
    set_area("hillside");
    set_areaname("outside of Bree");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("lush long");
    set_treetype("oak");

    set_add_forest();
    set_add_sky();

    set_extraline("The dense oak forest surrounds you on all sides. To " +
        "the west, Bree hill rises, blocking movement that way. It is " +
        "surrounded by a hedge. South is the the Great East road which " +
        "runs through the forest.");
    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees that grow here make up most of the " +
        "forest. They are tall and ancient looking. Their thick branches " +
        "spread out, blocking your view, and are covered with large " + 
        treetype + " leaves.\n");
    add_item(({"bree-hill", "bree hill"}),
        "This is a tall hill on the eastern edge of Bree. It runs north " +
        "and south, and forms the eastern border of Bree. Tall oak trees " +
        "over the hill, which make up the western part of the forest.\n");
    add_item("bree",
        "This important town lies on the other side of the hill. It cannot " +
        "be seen from the forest.\n");
    add_item(({"east road", "great east road", "great eastroad", "great road"}),
        "The road runs through " + areaname + " to the south. It is hard " +
        "to see it as it is mostly hidden from view.\n");
    add_std_herbs("hills");

    add_item(({"hedge"}),
        "The hedge grows around the outside of the town. It is very " +
        "thick and resembles a wall. It offers a measure of protection, " +
        "increased by a deep dike that has been dug to the right of " +
        "the hedge.@@ranger_descr@@\n");
    add_item(({"dike", "deep dike"}),
        "The dike is a very wide, deep trench that looks like it was " +
        "dug ages ago. Nonetheless, it is kept in good repair and " +
        "surrounds the town. It is outside the hedge and offers another " +
        "defense in protecting Bree.\n");
    add_item(({"bushes"}),
        "They grow thick together, making up the hedge that surrounds " +
        "the town.\n");
    add_item(({"hedge"}),
        "The hedge grows around the outside of the town. It is very " +
        "thick and resembles a wall. It offers a measure of protection, " +
        "increased by a deep dike that has been dug to the right of " +
        "the hedge. A path leads through a slight opening in the hedges.\n");
    add_item(({"dike", "deep dike"}),
        "The dike is a very wide, deep trench that looks like it was " +
        "dug ages ago. Nonetheless, it is kept in good repair and " +
        "surrounds the town. It is outside the hedge and offers another " +
        "defense in protecting Bree.\n");
    add_item(({"bushes"}),
        "They grow thick together, making up the hedge that surrounds " +
        "the town.\n");
    add_item(({"opening"}),
        "The opening is a thin place in the hedge.\n");
    add_item(({"path"}),
        "The path leads into a opening in the hedges. It also leads " +
        "northeast.\n");



    add_exit(ER_DIR + "br1_02", "northeast");

}


public void
init()
{
    ::init();
    add_action("enter_hedge", "enter");
}

int enter_hedge(string str)
{
    if(!str)
    {
        write("Enter what?\n");
        return 1;
    }

    if(str =="hedge" || str == "opening" || str == "gap")
    {
        write("You disappear into the hedge.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " enters the hedge.\n",TP);
        TP->move_living("M",ER_DIR + "erb2", 1);
        return 1;
    }
    else 
    {
        write("Enter what?\n");
        return 1;
    }
    
}
