/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road here continues towards Haven, turning slightly "+
      "to the west to curve around the foothills of the mountains which "+
      "stand in your way to the south. The road also continues northeast "+
      "into Shadow Canyon.\n");

    add_item(({"shadow canyon", "canyon", "Shadow Canyon"}), "The area "+
      "is named Shadow Canyon, probably because of the high walls that "+
      "cause shadows to fall across the valley in between.\n");

    add_exit(RDIR + "road3", "west");
    add_exit(RDIR + "road1", "northeast");

    OUTSIDE;
}

