/* West Street 2, VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("The street continues both north and south.\n");

    AE(VROOM + "ws1", "north", 0);
    AE(VROOM + "ws3", "south", 0);
}
