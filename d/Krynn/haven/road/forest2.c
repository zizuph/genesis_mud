/* Forest near Haven by Teth */

#include "/d/Krynn/haven/local.h"

inherit FORESTBASE;

void
create_forest()
{
    add_my_desc("The forest seems to get darker to the southwest. Paths " +
      "lead to the southwest, further into the forest, and east, back to " +
      "Haven.\n");

    add_item("paths","The paths are merely walkways through the thick " +
      "forest.\n");
    add_item("path","There is nothing special about the path.\n");

    add_exit(RDIR + "forest1", "east", 0, 3, 1);
    add_exit(RDIR + "forest3", "southwest", 0, 3, 1);

    OUTSIDE;
}
