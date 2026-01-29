/* Barrack 1, VK
 * by Teth, Dec 3, 1996
 */

#include "../local.h"

inherit BARRACK;

public void
create_barrack()
{
    add_my_desc("This barrack is extended to the southeast, " +
        "while leading back to the street to the north.\n");
    AE(VROOM + "sn2", "north", 0);
    AE(VROOM + "b2", "southeast", 0);
}
