/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills block movement in all directions to the west.\n");

    AE(TROOM + "valley6", "north", 0, 1);
    AE(TROOM + "valley12", "northeast", 0, 1);
    AE(TROOM + "valley13", "east", 0, 1);
    AE(TROOM + "valley14", "southeast", 0, 1);
    AE(TROOM + "valley8", "south", 0, 1);
    reset_tant_room();
}

