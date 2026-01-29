/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills block movement in all directions except north, " +
        "northeast, and east.\n");

    AE(TROOM + "valley7", "north", 0, 1);
    AE(TROOM + "valley13", "northeast", 0, 1);
    AE(TROOM + "valley14", "east", 0, 1);
    reset_tant_room();
}

