/* Forest near Haven by Teth */

#include "/d/Krynn/haven/local.h"

inherit FORESTBASE;

void
create_forest()
{
    add_my_desc("The forest seems to get darker to the southwest. Paths " +
      "lead northeast to Haven, and both west and south, further into " +
      "the forest.\n");

    add_item("paths","The paths are merely walkways through the thick " +
      "forest.\n");
    add_item("path","There is nothing special about the path.\n");

    add_exit(RDIR + "forest2", "northeast", 0, 3, 1);
    add_exit(RDIR + "forest4", "west", 0, 3, 1);
    add_exit(RDIR + "forest5", "south", 0, 3, 1);

    OUTSIDE;
}
