/*
 * Secret path for Rangers.
 * Branch 5. Runs through Trollshaws
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"
#include <composite.h>
#include <filter_funs.h>

inherit EAST_ROAD;

#define BUSHES     "/d/Shire/common/trollsh/shaws23"


void create_er_room()
{
    set_areadesc("dark");
    set_area("path in");
    set_areaname("the trollshaws");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_treetype("conifers");

    set_add_trollshaws();
    set_add_sky();
    add_std_herbs("hills");

    set_extraline("The path is dark and long shadows blanket it from the " +
        "trees. The dark forest grows to the south which block your view " +
        "that way. Ridges rise in the distance, and are bare except for " +
        "the bushes and stunted trees that grow on them. Thick bushes " +
        "block your way southeast.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the area.\n");
    add_item(({"bushes", "shrubs"}),
        "The bushes are thorny but scraggly looking. They grow scattered " +
        "across the area and some look large enough to block your passing. A path leads through one bush to the southeast. @@road_desc@@\n");


    add_exit(ER_DIR + "br5_08", "east");
    add_exit(ER_DIR + "br5_06", "west");

}

public void
init()
{
    ::init();
    add_action("leave_bushes", "enter");

}
int leave_bushes(string str)
{
    if(str=="bushes" || str == "shrub" | str == "shrubs")
    {
        write("You carefully part the bushes and go out to the Trollshaws.\n");
        say(QCTNAME(TP) + " carefully parts the bushes and goes out " +
            "to the Trollshaws.\n");
        TP->move_living("M",TS_DIR + "shaws23");
    }

    else write("Enter what?\n");
    return 1;
}


string
road_desc()
{
    object other_room;
    mixed opeople;
    string views;

// East on the old highway view
    if (!LOAD_ERR(BUSHES))
        other_room = find_object(BUSHES);
    else
        return "Error with BUSHES. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views =  "the Trollshaws look empty.\n";
    else
        views =  COMPOSITE_LIVE(opeople)+" is standing on the other side.\n";

    views = "Peering through the bushes, " + views;
    return views;

}

