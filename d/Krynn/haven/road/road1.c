/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road here leaves the mountains, and levels out on the "+
      "flat ground of the plains. Back northeast the road ascends into the "+
      "mountains, and winds its crooked path towards the Twin Peaks. It "+
      "also continues southwest towards Haven.\n");

    add_item(({"shadow canyon", "canyon", "Shadow Canyon"}), "The area "+
      "is named Shadow Canyon, probably because of the high walls that "+
      "cause shadows to fall across the valley in between.\n");

    add_exit(RDIR + "road2", "southwest");
    add_exit(RDIR + "mount_road1", "northeast", "@@mountains", 3);

    OUTSIDE;
}

int
mountains()
{
    write("You begin the journey upwards, ascending into the mountains on "+
      "the road towards Solace which passes through the Twin Peaks.\n");
    return 0;
}


