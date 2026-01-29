/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills block movement to the east and northeast.\n");

    AE(TROOM + "valley5", "southwest", 0, 1);
    AE(TROOM + "valley4", "west", 0, 1);
    AE(TROOM + "valley3", "northwest", 0, 1);
    AE(TROOM + "valley9", "north", 0, 1);
    AE(TROOM + "valley16", "southeast", 0, 1);
    AE(TROOM + "valley11", "south", 0, 1);
    reset_tant_room();
}

