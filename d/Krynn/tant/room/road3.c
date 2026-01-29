/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road bends here, continuing southwest and southeast.\n");

    AE(TROOM + "road2", "southwest", 0);
    AE(TROOM + "road4", "southeast", 0);
    reset_tant_room();
}

