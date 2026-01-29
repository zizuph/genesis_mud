/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road runs east and southwest through the foothills.\n");

    AE(TROOM + "road4", "southwest", 0, 2);
    AE(TROOM + "road6", "east", 0, 2);
    reset_tant_room();
}

