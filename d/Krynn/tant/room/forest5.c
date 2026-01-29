/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("The thickness of the forest prevents movement in many " +
        "directions, except to the north and south.\n");

    AE(TROOM + "forest6", "north", 0, 2, 1);
    AE(TROOM + "forest4", "south", 0, 2, 1);

    reset_tant_room();
}

