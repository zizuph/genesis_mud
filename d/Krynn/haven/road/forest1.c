/* Forest near Haven by Teth */

#include "/d/Krynn/haven/local.h"

inherit FORESTBASE;

void
create_forest()
{
    add_my_desc("The forest continues to the west, skirting an encampment " +
      "to the southeast. The road outside of Haven travelling north to " +
      "Solace can be reached by going east.\n");

    add_item("encampment","You can see no details of the encampment " +
      "from where you stand. You'd have to go to the east to get a better " +
      "vantage point.\n");
    add_item("road","The road is to the east.\n");

    add_exit(RDIR + "road10", "east", 0, 3, 1);
    add_exit(RDIR + "forest2", "west", 0, 3, 1);

    OUTSIDE;
}
