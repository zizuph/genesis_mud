/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road continues to the northeast and southwest.\n");

    AE(TROOM + "road3", "northeast", 0, 2);
    AE(TROOM + "road1", "southwest", 0);
    reset_tant_room();
}

