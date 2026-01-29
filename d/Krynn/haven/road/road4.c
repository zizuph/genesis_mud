/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road to Haven continues southwest here towards "+
      "the capital of Abanasinia, and northeast towards the pass between "+
      "Twin Peaks to the far northeast.\n");

    add_exit(RDIR + "road5", "southwest");
    add_exit(RDIR + "road3", "northeast");

    OUTSIDE;
}
