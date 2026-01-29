/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills block movement to the west and northwest.\n");

    AE(TROOM + "valley1", "southwest", 0, 1);
    AE(TROOM + "valley3", "north", 0, 1);
    AE(TROOM + "valley9", "northeast", 0, 1);
    AE(TROOM + "valley10", "east", 0, 1);
    AE(TROOM + "valley11", "southeast", 0, 1);
    AE(TROOM + "valley5", "south", 0, 1);
    reset_tant_room();
}

