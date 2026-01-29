/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Movement is allowed in all directions except east " +
        "and southeast.\n");

    AE(TROOM + "valley7", "southwest", 0, 1);
    AE(TROOM + "valley6", "west", 0, 1);
    AE(TROOM + "valley5", "northwest", 0, 1);
    AE(TROOM + "valley11", "north", 0, 1);
    AE(TROOM + "valley16", "northeast", 0, 1);
    AE(TROOM + "valley13", "south", 0, 1);
    reset_tant_room();
}

