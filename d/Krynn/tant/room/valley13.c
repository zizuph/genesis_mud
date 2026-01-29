/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills only prevent you from going northeast.\n");

    AE(TROOM + "valley8", "southwest", 0, 1);
    AE(TROOM + "valley7", "west", 0, 1);
    AE(TROOM + "valley6", "northwest", 0, 1);
    AE(TROOM + "valley12", "north", 0, 1);
    AE(TROOM + "valley17", "east", 0, 1);
    AE(TROOM + "valley18", "southeast", 0, 1);
    AE(TROOM + "valley14", "south", 0, 1);
    reset_tant_room();
}

