/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("You can go in all directions except northwest and  " +
        "southwest.\n");

    AE(TROOM + "valley1", "west", 0, 1);
    AE(TROOM + "valley4", "north", 0, 1);
    AE(TROOM + "valley10", "northeast", 0, 1);
    AE(TROOM + "valley11", "east", 0, 1);
    AE(TROOM + "valley12", "southeast", 0, 1);
    AE(TROOM + "valley6", "south", 0, 1);
    reset_tant_room();
}

