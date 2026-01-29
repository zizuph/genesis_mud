/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road here turns southeast as you near Haven, and "+
      "enters a narrow valley between the mountains to your north. "+
      "Far to the south you spot the forests of Qualinesti, which "+
      "only elves would enter without unease. The Kharolis mountains "+
      "travel as far south as you can see, beyond even the vast forest "+
      "of the elves.\n");

    add_exit(RDIR + "road6", "north", "@@valley");
    add_exit(RDIR + "road8", "southeast");

    OUTSIDE;
}

int
valley()
{
    write("You travel north into the valley between the Kharolis mountains "+
      "to your west, and the sentinels of Darken Wood to your east.\n");
    return 0;
}
