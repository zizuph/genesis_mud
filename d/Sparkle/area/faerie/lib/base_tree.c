#include "defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>

#define NEED_CLIMB_SKILL    15

void up_tree();
void down_tree();

string up_room, down_room;


void up_tree()
{
    write("You reach up and grab an overhanging branch and pull " +
        "yourself up. With a great deal of effort, you climb " +
        "several branches and go farther up into the tree.\n");
    say(QCTNAME(TP) + " reaches up and grabs an overhanging branch. " +
        "With a great deal of effort, " + CAP(HE_SHE(TP)) + " climbs " +
        "several branches and goes farther up into the tree.\n");
    TP->move_living("M",up_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}

void down_tree()
{
    write("You carefully climb down several branches.\n");
    say(QCTNAME(TP) + " carefully climbs down several branches.\n");
    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from above.\n",TP);
}
