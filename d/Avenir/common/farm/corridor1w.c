#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/d/Avenir/inherit/avenir_time.c";
inherit "/std/room";

void
create_room()
{
    set_short("The western corridor");
    set_long("This is the western corridor of the second " +
        "floor of the house. A small door into a bedroom " +
        "is all you see except from the window in the " +
        "west wall.\n");
    add_item("window","You try to open the window but its " +
        "impossible. Looking through the dirty " +
        "glass you see the grass lawn surrounding the " +
        "house. On the lawn is a tall tree.\n");
    add_item("tree","Looking at the tree you spot a " +
        "small well hidden bird nest among the branches. " +
        "It strikes you that its probably impossible to " +
        "see the nest from an angle different than this.\n");
    add_item(({"lawn","grass lawn"}),"Outside, below the window, the " +
        "grass lawn stretches out to the hedge. Only a tall " +
        "tree can be seen on the lawn from up here.\n");
    add_item("hedge","You look over the grass lawn at the hedge. Its " +
    "high and well grown and its impossible to see anything through " +
        "or behind it from this distance.\n");
    add_item(({"corridor", "broad corridor"}),
        "It is a wide corridor. Your imagination gives it gleaming "+
        "hardwood floors, a runner of reddish carpet, and wall sconces, "+
        "but you cannot hold the image and it reverts to what it is: "+ 
        "a dusty, neglected corridor running east and west along the "+
        "length of the house. You measure the corridor to be approximately 18 feet wide.\n");
    add_item(({"nest","bird nest"}),"@@nest_desc@@" + "\n");
    add_exit("bedroom_w","north");
    add_exit("platform","east");
    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
        add_action("open_window","open");
        add_action("search_far_away_items","search");
}

string
nest_desc()
{
    string text;
    text = "Between the branches you catch a glimpse of the nest.";
    text += " Now the nest is empty as the dark months " +
        "has arrived.";
    object room = find_object("west_side");
    if (room)
        if (room->query_ring())
            text += "No sign of a bird can be seen but you " +
                " see something glittering in the nest.";
    return text;
}


int
search_far_away_items(string str)
{
    if (str == "nest")
    {
        write("The " +str+ " is too far away to search.\n");
        return 1;
    }
    return 0;
}
 

int
open_window(string str)
{

    if ((str) && (str == "window"))
    {
        write("You walk up to the window and try to open it. " +
            "Its doesnt give after one tiny bit though. " +
            "Probably someone hit a nail or two in it from the " +
            "outside, but you cannot tell for sure.\n");
        say(({METNAME + " tries to open the window but it seems " +
            "to be stuck and it wont open.\n",
            TART_NONMETNAME + " tries to open the window but it seems " +
            "to be stuck and it wont open.\n",
            "You hear a noice from the window.\n"}), TP);
        return 1;
    }
    return 0;

}

