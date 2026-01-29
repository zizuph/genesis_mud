/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit MOUNTBASE;

void
create_mountain()
{
    add_my_desc("You are in what is called Shadow Canyon, southwest of "+
      "the pass between Twin Peaks. The road descends from the mountains "+
      "to the southwest, continuing towards Haven. The pass is steep and "+
      "sometimes hard-going, but it is possible.\n");

    add_item(({"shadow canyon", "canyon", "Shadow Canyon"}), "The area "+
      "is named Shadow Canyon, probably because of the high walls that "+
      "cause shadows to fall across the valley in between.\n");

    add_exit(RDIR + "road1", "southwest", "@@mountains", 3);
    add_exit(RDIR + "mount_road2", "northeast", "@@mountains2", 3);

    OUTSIDE;
}

int
mountains()
{
    write("You descend from the mountains, onto the flat lands below.\n");
    return 0;
}

int
mountains2()
{
    write("You continue your ascent into Shadow Canyon, making your way "+
      "northeast towards the pass between Twin Peaks.\n");
    return 0;
}
