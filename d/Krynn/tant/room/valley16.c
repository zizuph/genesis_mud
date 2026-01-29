/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills allow movement to all points west, and north.\n");

    AE(TROOM + "valley12", "southwest", 0, 1);
    AE(TROOM + "valley11", "west", 0, 1);
    AE(TROOM + "valley10", "northwest", 0, 1);
    AE(TROOM + "valley15", "north", 0, 1);
    reset_tant_room();
}

