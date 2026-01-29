/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
#include <macros.h>
//#include "/d/Shire/private/shire_admin.h"
 
inherit FOREST_BASE;

object ranger;

void
create_forest_room()
{
    if (interactive(this_player()))
        catch(call_other(RNPC_DIR + "clone_handler", "??"));
    set_extraline("The ridge is covered with small groups " +
        "of trees and offers a panoramic view of a valley " +
        "below. Stands of deciduous trees are visible in the " +
        "valley.\n");
    add_item(({"ribbon", "river", "thin ribbon","glittering river"}),
        "It twinkles in the distance, but it is hard to see what " +
        "it could be.\n");
    add_item("white stone",
        "You see a white stone. The hidden stone seems out of " +
        "place here. It lays in the bushes undetected except " +
        "by trained eyes. A star is engraved on the bottom of " +
        "the stone, half buried beneath the ground. A moon is " +
        "engraved on the left-hand side of the stone.\n");
    add_item(({"deciduous trees", "deciduous tree", "deciduous"}),
        "Large beech and oak trees cover the valley below.\n");
    add_item("ridge",
        "Hidden among the bushes and shrubs, you see a path " +
        "which descends down the side of the ridge.\n");
    add_item(({"valley"}),
        "A valley stretches out before you below the ridge. " +
        "Below you see stands of what appears to be trees. In " +
        "the distance you see a thin ribbon, most likely a " +
        "river, glittering in the the valley.\n");
    add_item(({"moss", "mosses"}),
        "A velvet carpet of soft green moss grows on some of " +
        "the logs here. Some silver-grey moss hangs from " +
        "the tree branches.\n");
    add_item(({"stones", "rocks"}),
		"Various rocks and stones are buried under the leaves. They " +
        "look like they have been washed down from the " +
        "mountains and are of various colors.\n");
    add_item(({"colored stones", "colored rocks"}),
        "You see some red, gray, black, white, and other " +
        "colored stones scattered about.\n");
    add_item(({"black stones", "black rocks", "red stones", "red rocks", 
            "white stones", "white rocks", "gray stones", 
            "gray rocks"}),
        "The stones are scattered about, some buried under the " +
        "leaves and forest debris.\n");
    reset_shire_room();
    add_forest_herbs();
 
    add_exit(FOREST_DIR + "forest18", "south","@@bush_exit@@",4, check_person);
    add_exit(FOREST_DIR + "track07",  "west", 0,4, check_person);
    add_exit(VALLEY_DIR + "stairs01", "down", "@@to_valley@@", 3,1);
 
 
}
 
 
string short_desc() 
{
    return "A ridge overlooking a valley in the Misty Mountains";
}

int bush_exit()
{
    write ("You go south and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes south and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest18",
        QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
        TP);


}
void reset_shire_room()
{
    if (!objectp(ranger))
    {
	ranger = clone_object(RANGER_NPC+"n_ranger");
	ranger->arm_me();
	ranger->add_prop(OBJ_I_HIDE, 50);
	ranger->move(TO);
    }
}

void to_valley()
{
//    TELL_ADMIN(TP->query_cap_name() + ", ("+TP->query_alignment()+
//        ") entered Rivendell at " + ctime(time()));
}