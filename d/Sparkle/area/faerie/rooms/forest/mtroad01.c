/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include <ss_types.h>
#include <macros.h>
#include "defs.h"

inherit FOREST_BASE;

#define ORC_VALLEY  "/d/Genesis/start/human/wild2/orc_road4"

void up_tree();

string extra_line = "", 
       up_room = FOREST_DIR + "mtroad01u1",
       this_room = "mtroad01";

void
create_forest_room()
{
    set_short("Near the Orc valley");
    set_long(short() + ". @@s_desc_sky_outside_sky@@" + 
    "The valley is deep and runs to the south. The mountains rise around " +
    "you, surrounding you with tall fir trees. The track wanders east " +
    "towards a valley and west into the mountains." + extra_line + 
    " Some bees buzz around the upper branches of the tree.\n");

    set_add_valley();
    add_std_herbs("forest");
    set_conifer_trees();
    set_add_forest_debris();
    set_add_bees();
    reset_room();

    add_exit(ORC_VALLEY,  "east");
    add_exit(FOREST_DIR + "mtroad02", "west");
}

void
reset_room()
{
    object npc;
    string npc_file_name = SETTLER,
        npc_name = FAERIE + npc_file_name + "_";

    if (!present(npc_name)) 
    {
        npc = clone_object(NPC_DIR + npc_file_name);
        npc->move(TO);
    }

    set_searched(0);
}


public void
init()
{
    ::init();
    add_action("do_climb", "climb");

}


int do_climb(string str)
{
    int player_climb_skill;
    if(!str)
    {
        write("Climb what? \n");
        return 1;
    }

    player_climb_skill = TP->query_skill(SS_CLIMB);

    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb up?\n");
        return 1;
    }

    if(str=="up")
    {
        if(player_climb_skill>NEED_CLIMB_SKILL)
        {
            up_tree();
        }
        else
        {
            write("You struggle and try to climb the tree, but " +
                "are unable to do so.\n");
            say(QCTNAME(TP) + " struggles to climb the tree but " +
                "is unable to.\n");
        }
    }
    else write("Climb what?\n");
    return 1;
}


void up_tree()
{
    write("You reach up and grab an overhanging branch and pull " +
        "yourself up. With a great deal of effort, you climb " +
        "several branches and go farther up into the tree.\n\n");
    say(QCTNAME(TP) + " reaches up and grabs an overhanging branch. " +
        "With a great deal of effort, " + CAP(HE_SHE(TP)) + " climbs " +
        "several branches and goes farther up into the tree.\n");
    TP->move_living("M",up_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}
