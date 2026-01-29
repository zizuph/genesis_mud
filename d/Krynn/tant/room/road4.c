/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road forms a hook, continuing northwest and " +
        "northeast.\n");

    AE(TROOM + "road3", "northwest", 0, 2);
    AE(TROOM + "road5", "northeast", 0, 2);
    reset_tant_room();
}

