/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("This is a small valley between some foothills. A forest " +
        "is settled within the foothills to the southeast, while the road " +
        "continues west and northeast.\n");
    AI(({"valley","small valley"}),"It is nestled between two foothills.\n");
    AI("forest","The forest seems to be rather expansive.\n");

    AE(TROOM + "road6", "west", 0, 2);
    AE(TROOM + "road8", "northeast", 0, 2);
    AE(TROOM + "forest6", "southeast", 0, 2, 1);
    reset_tant_room();
}

