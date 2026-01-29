/* West Street 3, New VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("A tall building stands to the east, its frontage " +
        "facing the north-south street.\n");
    AI(({"tall building","official building","building"}),"This is an " +
        "official building, stately in its look and frontage.\n");
    AI("frontage","Displayed on the frontage is a placard.\n");
    AI("placard","The placard reads:\n\nOffice of Vingaard Keep\n\n");
    ACI("placard","read","The placard reads:\n\nOffice of " +
        "Vingaard Keep\n\n");

    AE(VROOM + "ws2", "north", 0);
    AE(VROOM + "board_office", "east", 0);
    AE(VROOM + "ws4", "south", 0);
}
