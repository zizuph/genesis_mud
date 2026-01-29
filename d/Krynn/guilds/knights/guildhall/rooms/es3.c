/* East street 3, VK
 * By Teth, Dec. 3 1996
 * Changed pigeons to doves to correct typo. Damaris@Genesis 3/2005
 */


#include "../../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("The street continues north and south, and " +
        "there is a small hut to the west.\n");
    AI(({"hut","small hut"}),"This hut is constructed in " +
        "an odd way, with holes in the roof.\n");
    AI(({"holes","holes in the roof","roof"}),"The holes in the " +
        "roof look to be used by some flying creature... doves!\n");

    AE(VROOM + "pigeon_store", "west", 0);
    AE(VROOM + "es2", "north", 0);
    AE(VROOM + "es4", "south", 0);
}
