/*
 *  This is tree2.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h";

void
create_room()
{
    set_short("in the branches of a tree atop Amon Din");
    set_long(BSN(
       "Large limbs jut out from the center of this tree which"
     + " rises still a good distance above. The edge of a rooftop"
     + " is visible through the branches to the north, while the"
     + " view in all other directions is obscured by the thick"
     + " mesh of branches. Below lies the ground at the base of"
     + " the tree."));
    add_item(("view"), BSN(
       "The branches have thinned some here, but are still too"
     + " bushy to allow for any appreciation of the view."));
    add_item(({"limbs","limb","branch","branches","roof",
      "rooftop","edge"}), BSN(
       "Most of the limbs here are long and thick. A number of"
     + " them have extended out onto the roof to the north."));
    add_item(({"tree","center"}), BSN(
       "This tree is truly massive, perhaps having weathered three"
     + " hundred years atop this peak. It may be possible to climb"
     + " farther up from here."));
    add_item(({"below","ground","base"}), BSN(
       "The drop to the ground seems too far to risk. Climbing"
     + " down seems to be the only option."));

    add_exit(AMON_DIR + "tree3", "up", "@@climb_up");
    add_exit(AMON_DIR + "tree1", "down");
}

int
climb_up()
{
    int climb = TP->query_skill(SS_CLIMB);

    if (climb < 25)
    {
        write BSN("You cannot seem to navigate the branches in"
                + " that direction.");
        say(QCTNAME(TP) + " struggles to climb higher, but cannot.\n");
        return 1;
    }
    else
        write("You climb carefully up through the thick branches.\n");
    return 0;
}

int
do_climb(string str)
{
    if (!strlen(str))
    {
    NFN("Climb where?");
        return 0;
    }

    if (str != "roof" && str != "rooftop")
    {
        NFN("Where do you want to climb?");
        return 0;
    }

    write("You climb out on the branches and onto the rooftop.\n");
    say(QCTNAME(TP) + " climbs out on the branches and onto the roof"
      + "top.\n");
    TP->move_living("M",AMON_DIR + "roof2", 1);

    return 1;
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}
