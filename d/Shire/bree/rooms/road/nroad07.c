/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

#define GIRD_DIR    "/d/Shire/eastroad/girdley/"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("It looks treacherous as the land appears " +
        "more desolate the further north you look. The land is " +
        "marshy with hills rising in the distance.\n");
    add_item(({"hills"}),
        "They rise in the distance to the north. They appear rounded, " +
        "showing their age from countless years of weathering by " +
        "the elements. @@ranger_descr@@\n");
    add_item(({"ravine"}),
        "@@ravine_descr@@\n");
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

    set_add_nroad();

    add_exit(ARNOR_DIR + "nr3", "north");
    add_exit(ROAD_DIR + "nroad06", "south");


}


// initializes the action
public void
init()
{
    ::init();
    add_action("enter_ravine", "enter");
}

// moves them there secretly
void find_entrance()
{

    write("You carefully climb down and enter the ravine.\n");
    TP->move_living("M", GIRD_DIR + "secret06",1);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from road.\n",TP);
}


// defines the action
int enter_ravine(string str)
{

    if (R_ALLOWED)
    {    
        if(!str)
        {
            write("Enter what? \n");
            return 1;
        }

        if(str =="ravine")
        {
            find_entrance();
            return 1;
        }
        else 
        {
            write("Enter ravine?\n");
            return 1;
        }
    }
    
}


// lets rangers see it in general
string ranger_descr()
{
    if (R_ALLOWED)

        return "Looking closer, you see a ravine hidden among bushes " +
            "and trees. ";
    else
        return "";

}

// lets them see it in detail.
string ravine_descr()
{
    if (R_ALLOWED)
    
        return "The ravine is barely visible in the distance. It is " +
            "hidden by trees, bushes, and hills around here. It looks " +
            "like you may be able to enter it.";
    else
        return "You find no ravine.";

}
