/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("Northeast and southeast are the two directions that the " +
        "road continues to run.\n");

    AE(TROOM + "road12", "northeast", 0, 2);
    AE(TROOM + "road10", "southeast", 0, 2);
    reset_tant_room(); 
}

