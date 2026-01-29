/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills only allow movement to the west, southwest " +
        "and south.\n");

    AE(TROOM + "valley4", "southwest", 0, 1);
    AE(TROOM + "valley3", "west", 0, 1);
    AE(TROOM + "valley10", "south", 0, 1);

    reset_tant_room();
}

