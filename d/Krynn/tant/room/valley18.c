/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;


public void
create_valley()
{
    add_my_desc("Foothills block movement in all directions to the east " +
        "and south.\n");

    AE(TROOM + "valley14", "west", 0, 1);
    AE(TROOM + "valley13", "northwest", 0, 1);
    AE(TROOM + "valley17", "north", 0, 1);
    reset_tant_room();
}

