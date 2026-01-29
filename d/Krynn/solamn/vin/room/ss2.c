/* Street south 2, new VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("To the north rests a building with a sign by " +
        "the door. The street runs east and west.\n");
    AI("building","The building appears to be newly renovated, " +
        "but it does not look out of place.\n");
    AI("door","The door is open, inviting all to enter.\n");
    ACI("door","open","But the door is already open!\n");
    ACI("door","close","It seems to be lodged in place.\n");
    AI("sign","The sign reads:\n\nVingaard Keep General Store\n\n");
    ACI("sign","read","The sign reads:\n\nVingaard Keep General " +
        "Store\n\n");

    AE(VROOM + "ss1", "west", 0);
    AE(VROOM + "general_store", "north", 0);
    AE(VROOM + "ss3", "east", 0);
}
