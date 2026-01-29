/* Forest near Haven by Teth */

#include "/d/Krynn/haven/local.h"

inherit FORESTBASE;

void
create_forest()
{
    add_my_desc("The forest seems to get darker to the west. Paths lead " +
      "north and west, but you also notice something what might be an " +
      "animal trail leading southeast.\n");

    add_item("paths","The paths are merely walkways through the thick " +
      "forest.\n");
    add_item("path","There is nothing special about the path.\n");
    add_item(({ "trail", "animal trail"}),
      "A barely noticable animal trail leads deeper into the woods to " +
      "the southeast.\n");
      
    add_exit(RDIR + "forest3", "north", 0, 3, 1);
    add_exit(RDIR + "forest6", "west", 0, 3, 1);
    add_exit("/d/Krynn/qualinesti/forest/hentrance", "southeast", 0, 2, 1);
    
    OUTSIDE;
}
