/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("The thickness of the forest prevents movement in many " +
        "directions, except to the northwest and southwest.\n");

    AE(TROOM + "forest6", "southwest", 0, 2, 1);
    AE(TROOM + "road8", "northwest", 0, 2, 1);

    reset_tant_room();
}

