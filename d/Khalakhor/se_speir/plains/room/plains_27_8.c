#include "plains.h"

inherit PLAINBASE;
inherit SR_DIR+"lib/branchcmd";

public void
reset_room()
{
   set_searched(0);
   set_numbranches(2);
}


public void
create_khalakhor_room()
{
    proxim = (["river"  : ({0, "west"})]);
    create_plain();
    set_short("On a narrow path on a grassy plain");
    set_long("   You are walking along a narrow path on a wide grassy "+
             "plain covered in rolling hills near a river. To the "+
             "east is a fenced-in area, probably the property and "+
             "livelihood of those who live in the house to the "+
             "south. The river rolls along quietly to the west, "+
             "a willow tree growing along its bank, "+
             "a cool breeze bringing the scent of salt air and "+
             "thick clouds above.\n");

    add_item(({"house","home","dwelling"}),
       "It is a one-level, and probably one-room, rural home made "+
       "of large irregular stones masoned together, with a thatched "+
       "roof and a chimney.\n");
    add_item(({"tree","willow"}),
       "It is a common willow tree often found growing on the banks "+
       "of rivers. Its long flimsy branches fall down onto the ground, "+
       "some reaching into the river's waters.\n");
    add_item("path",
       "It is a narrow foot-trodden path through the grasses of "+
       "the plain, leading from the yard of the home to the "+
       "southwest into the pasture to the east.\n");
    add_item(({"area","fenced-in area","pasture"}),
       "There is what seems to be a pasture to the east, a "+
       "fenced-in area where livestock of some sort are probably "+
       "kept. An occassional shift in the wind confirms to your "+
       "nostrils that livestock is nearby.\n");
    add_item("fence",
       "The fence is crudely made of twisted, sun and rain warped "+
       "wooden beams, posts set fairly evenly around the pasture, "+
       "with two rails strapped horizontally between each. There "+
       "is a small opening in the fence to the east.\n");

    set_branchnum(6); // willow
    set_numbranches(2);
    add_exit(PLAINS + "plains_28_8", "east");
    add_exit(PLAINS + "plains_26_9", "southwest");
}

public int *
query_global_coords()
{
    return ({3, 0});
}

public void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
