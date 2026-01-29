/*
 * Secret path for Rangers.
 * Branch 1. Runs from Bree to Weathertop
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

#define WTOP    "/d/Shire/wtop/"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("rocky");
    set_area("path in");
    set_areaname("the rolling hills");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("sparse gray");
    set_treetype("dead");

    set_add_weather_hills();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("Rolling hills surround you and run northwest and " +
        "southeast. The land is rocky and covered with small bushes " +
        "and grasses. A path runs northeast through the hills. It also " +
        "runs west away from the hills and and east to a pile of rubble.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the hills to the northeast, west, and east to a pile of rubble.\n");
    add_item(({"rubble", "pile of rubble"}),
        "This is a pile of broken stones and rocks that were thrown " +
        "here during the many wars that occured in the region. The " +
        "rubble covers the path that leads east.\n");
    add_item(({"broken stones", "broken rocks"}),
        "They are various sizes of rocks and stones that were once " +
        "carved and used in this region. The stones and rocks have " +
        "weathered edges that were probably smooth at one time. Now " +
        "they are broken and lay in piles nearby.\n");

    add_exit(ER_DIR + "br3_01", "northeast");
    add_exit(ER_DIR + "br1_13", "west");

}

public void
init()
{
    ::init();
    add_action("enter_rubble", "climb");
}

int enter_rubble(string str)
{
    if(!str)
    {
        write("Climb what?\n");
        return 1;
    }

    if(str =="rubble" || str == "over rubble")
    {
/*
        write("You climb over the pile of rubble.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " climbs over a pile of rubble.\n",TP);
        TP->move_living("M", WTOP_DIR + "road08", 1);
*/
        write("The pile of rubble is too tall to climb over.\n");
        return 1;
    }
    else 
    {
        write("Climb what?\n");
        return 1;
    }
    
}
