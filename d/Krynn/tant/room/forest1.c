/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("The thickness of the forest prevents movement in many " +
        "directions, except to the northeast and southwest.\n");

    AE(W_ROAD, "southwest", 0, 2, 1);
    AE(TROOM + "forest2", "northeast", 0, 2, 1);

    reset_tant_room();
}

