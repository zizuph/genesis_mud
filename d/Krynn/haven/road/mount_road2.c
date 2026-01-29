/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit MOUNTBASE;

void
create_mountain()
{
    add_my_desc("You are in the pass between Twin Peaks. They tower over "+
      "you to the north and south, the tips vanishing into the clouds. "+
      "The road to Haven turns southwest into Shadow Canyon here, "+
      "descending towards the plains to the west. The road also travels "+
      "east, descending slightly as it leads towards Sentinel Gap.\n");

    add_item(({"shadow canyon", "canyon", "Shadow Canyon"}), "The area "+
      "is named Shadow Canyon, probably because of the high walls that "+
      "cause shadows to fall across the valley in between.\n");

    add_exit(RDIR + "mount_road1", "southwest", "@@mountains", 3);
    add_exit(RDIR + "mount_road3", "east", "@@mountains2", 3);

    OUTSIDE;
}

int
mountains()
{
    write("You descend from the pass into Shadow Canyon.\n");
    return 0;
}

int
mountains2()
{
    write("You descend into the path known as Sentinel Gap.\n");
    return 0;
}
