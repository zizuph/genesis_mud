/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills block movement to the southeast and " +
        "northeast.\n");

    AE(TROOM + "valley6", "southwest", 0, 1);
    AE(TROOM + "valley5", "west", 0, 1);
    AE(TROOM + "valley4", "northwest", 0, 1);
    AE(TROOM + "valley10", "north", 0, 1);
    AE(TROOM + "valley16", "east", 0, 1);
    AE(TROOM + "valley12", "south", 0, 1);
    reset_tant_room();
}

