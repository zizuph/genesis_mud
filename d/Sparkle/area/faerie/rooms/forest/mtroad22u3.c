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
string down_room = FOREST_DIR + "mtroad22u2";

void down_tree();

void
create_forest_room()
{
    FIXEUID;
    set_short("Near the top of a tall tree");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The branches " +
        "thin here near the top of the tree. They block your view of the " +
        "rest of the forest, and scratch you. A hive hangs from a branch. " +
        "Bees buzz around it and you.\n");

    reset_room();
    set_pine_branches();
    set_up_trees();
    set_add_bees();

    room_add_object(OBJ_DIR + "hive");
}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");

}

int do_climb(string str)
{

    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb down?\n");
        return 1;
    }

    if(str=="down")
    {
        down_tree();
        return 1;
    }
    
    write("Climb down?\n");
    return 1;
}


void down_tree()
{
    write("You carefully climb down several branches to the road below.\n\n");
    say(QCTNAME(TP) + " carefully climbs down several branches.\n");
    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from above.\n",TP);
}
