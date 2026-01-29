/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("The thickness of the forest prevents movement in many " +
        "directions, except to the north and southeast.\n");

    AE(TROOM + "forest5", "north", 0, 2, 1);
    AE(TROOM + "forest3", "southeast", 0, 2, 1);

    reset_tant_room();
}

