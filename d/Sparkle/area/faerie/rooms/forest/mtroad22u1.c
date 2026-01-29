/*
 * Upper branches of a tree
 * By Finwe, December 2005
 */

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

inherit FOREST_BASE;
string up_room = FOREST_DIR + "mtroad22u2", 
       down_room = FOREST_DIR + "mtroad22";
void up_tree();
void down_tree();

void
create_forest_room()
{
    FIXEUID;
    set_short("Up in a tall tree");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The tree is " +
        "tall with branches that hang over the road. They block your " +
        "view below but look large enough so that you can climb further " +
        "up into the tree. A buzzing sound can be heard from higher up " +
        "in the tree.\n");

    reset_room();
    set_pine_branches();
    set_up_trees();
    set_add_bees();
}


public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}


void
reset_room()
{
}


int do_climb(string str)
{

    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb up or down?\n");
        return 1;
    }

    if(str=="up")
    {
        up_tree();
        return 1;
    }
    
    if(str=="down")
    {
        down_tree();
        return 1;
    }
    
    write("Climb up or down?\n");
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

void down_tree()
{
    write("You carefully climb down several branches to the road below.\n\n");
    say(QCTNAME(TP) + " carefully climbs down several branches.\n");
    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from above.\n",TP);
}
