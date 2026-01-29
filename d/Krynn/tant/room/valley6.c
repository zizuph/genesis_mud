/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills block movement west and southwest.\n");

    AE(TROOM + "valley1", "northwest", 0, 1);
    AE(TROOM + "valley5", "north", 0, 1);
    AE(TROOM + "valley11", "northeast", 0, 1);
    AE(TROOM + "valley12", "east", 0, 1);
    AE(TROOM + "valley13", "southeast", 0, 1);
    AE(TROOM + "valley7", "south", 0, 1);
    reset_tant_room();
}

