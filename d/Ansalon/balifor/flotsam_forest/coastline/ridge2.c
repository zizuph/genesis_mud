#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("treacherous ridge");
    set_long("@@long_descr");

    add_item(({"cliffside","ridge","cliff"}),
      "You are balancing yourself on less than four inches of " +
      "a narrow ridge situated in the middle of a 100 foot high " +
      "cliff over the violent waters of the Bloodbay. Who said " +
      "an adventurer's life was ever dull?\n");
    add_item(({"violent waters","waters","bloodbay","Bloodbay"}),
      "You look down the fifty foot drop at the turbulent waters " +
      "beneath you, and then wish you hadn't as vertigo hits " +
      "you, making your head spin.\nYou feel slightly dizzy.\n");

    add_invis_exit(CROOM + "ridge1","southeast",0);
    add_invis_exit(CROOM + "ridge3","north",0);


    reset_flotsam_room();
}

string
long_descr()
{
    return "You question your wisdom as you balance yourself " +
    "on a few inches of cliffside that supports you from " +
    "plummeting into the violent waters of the Bloodbay " +
    "below you. " +
    "The ridge you stand on edges its way along the side of " +
    "the cliff to the " +
    "north and southeast.\n";
}
