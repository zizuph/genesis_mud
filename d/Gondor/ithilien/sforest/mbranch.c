inherit "/d/Gondor/ithilien/sforest/on_tree.c";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_on_tree()
{
    set_short("a branch halfway up a giant oak");
    set_description("You are standing on a branch of a giant oak "
      + "in a forest somewhere in southern Ithilien. You guess you "
      + "are about halfway up on the way to the top of the tree.");
    set_extraline("Thick branches covered with green leaves block "
      + "the view in all directions. You might manage to climb up "
      + "or down.");

    add_item(({"oak","oak tree","closer oak","nearer oak","second oak",
        "next oak","smaller oak"}), BSN(
        "This is a giant tree with an enourmous trunk. You guess "
      + "that your halfway between the ground and the top of the oak."));
    add_item(({"branch","branches","bough","boughs","leaves"}), BSN(
        "All the branches of the oak tree are densely covered with "
      + "thick green leaves. The branch you are standing on is "
      + "somewhere about halfway up the oak. It is thicker than a man's "
      + "thigh and probably could hold several people. The other branches "
      + "are similar. Growing closely together, they block the view in "
      + "all directions, but you might manage to climb further up or down."));

    set_up_room(ITH_DIR + "sforest/lookout");
    set_down_room(ITH_DIR + "sforest/lbranch");
}

