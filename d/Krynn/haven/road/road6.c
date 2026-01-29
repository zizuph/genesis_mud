/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("You stand between two mountain ranges: the mighty "+
      "Kharolis range to your west, and the smaller range of mountains "+
      "which surrounds the haunted forest of Darken Wood to your east. "+
      "The valley, about a mile wide, emerges into rolling plains "+
      "to both the north and the south.\n");

    add_exit(RDIR + "road5", "north", "@@valley");
    add_exit(RDIR + "road7", "south", "@@valley");

    OUTSIDE;
}

int
valley()
{
    write("You emerge from the valley, and the Kharolis mountains retreat "+
      "back to the east, leaving rolling plains in their place.\n");
    return 0;
}
