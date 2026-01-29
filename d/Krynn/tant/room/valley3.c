/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills block movement in all directions to the west, " +
        "and the northeast as well.\n");

    AE(TROOM + "valley2", "north", 0, 1);
    AE(TROOM + "valley9", "east", 0, 1);
    AE(TROOM + "valley10", "southeast", 0, 1);
    AE(TROOM + "valley4", "south", 0, 1);
    reset_tant_room();
}

