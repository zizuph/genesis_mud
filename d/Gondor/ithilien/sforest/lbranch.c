inherit "/d/Gondor/ithilien/sforest/on_tree.c";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_on_tree()
{
    set_short("the lowest branch of a giant oak");
    set_description("You are in a giant oak in a forest somewhere "
      + "in southern Ithilien.");
    set_extraline("This is the lowest branch of the oak. Below the "
      + "branch a large rock is rising in a thicket of bushes close to "
      + "the tree trunk. Thick branches covered with green leaves "
      + "block the view in all directions. You can climb up, or you "
      + "might manage to climb down from the branch onto the rock.");
    add_item(({"bush","bushes","thicket"}),
        "The oak is surrounded by a dense thicket of bushes.\n");
    add_item(({"ash","ash tree","ashes","ash trees","forest","tree","trees"}),
        BSN("In the midst of the thicket there are a few ash trees. "
      + "They are not very tall, standing in the shadow of the two giant "
      + "oaks."));
    add_item(({"oaks","oak trees"}), BSN(
        "These are two giant trees, rising many metres into the sky. "
      + "The one farther from you is even larger than the one you have "
      + "climbed."));
    add_item(({"large oak","larger oak","first oak","farther oak",
        "further oak","other oak"}), BSN(
        "This is a really giant oak tree. You estimate its height to "
      + "about forty yards. The trunk is so thick that three men could "
      + "not embrace it."));
    add_item(({"oak","oak tree","closer oak","nearer oak","second oak",
        "next oak","smaller oak"}), BSN(
        "This is a giant tree with an enourmous trunk, even though it "
      + "is somewhat smaller than the other oak."));
    add_item(({"branch","branches","bough","boughs","leaves"}), BSN(
        "All the branches of the oak tree are densely covered with "
      + "thick green leaves. The branch you are standing on is the "
      + "lowest branch of the oak. It is thicker than a man's thigh "
      + "and probably could hold several people. The other branches "
      + "are similar. Growing closely together, they block the view in "
      + "all directions, but you might manage to climb further up."));
    add_item(({"rock","large rock"}), BSN(
        "The large rock is directly under the branch on which you are "
      + "standing. Cracks are running through the rock, and there are "
      + "several sharp edges which probably would hurt you if you fell "
      + "down from the branch onto the rock."));

    set_up_room(ITH_DIR + "sforest/mbranch");
    set_down_room(ITH_DIR + "sforest/on_rock");
}

void
climb_down()
{
    write("You climb down from the branch onto the top of the rock.\n");
    tell_room(TO, QCTNAME(TP) + " climbs down from the branch onto the top of the rock.\n",TP);
    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing down from the oak.\n",TP);
}

void
fall_down(int hit)
{
    write("You try to climb down from the branch.\n"
        + "Suddenly you slip ...\n"
        + "You fall down from the branch and painfully land on the top of the rock.\n");
    tell_room(TO, QCTNAME(TP) + " tries to climb down from the branch, but slips.\n"
        + CAP(TP->query_pronoun()) + " falls down from the branch and lands on top of the rock.\n",TP);

    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives falling down from above.\n",TP);
    TP->reduce_hit_point(hit);
    if (TP->query_hp() <= 0)
        TP->do_die(TO);
}

