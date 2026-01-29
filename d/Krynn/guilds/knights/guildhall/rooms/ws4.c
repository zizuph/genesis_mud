/* West street 4, New VK
 * By Teth, Dec. 3 1996
 */


#include "../../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("The street continues north and south.\n");

    AE(VROOM + "ws3", "north", 0);
    AE(VROOM + "ws5", "south", 0);
}
