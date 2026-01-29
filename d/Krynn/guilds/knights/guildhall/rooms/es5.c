/* East street 2, VK
 * By Teth, Dec. 3 1996
 */


#include "../../guild.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("To the east is a low building, with high " +
        "entranceways. The street continues to the north and " +
        "south.\n");
    AI(({"building","low building"}),"This building emits the " +
        "twin smells of horse manure and hay. It must be a " +
        "stable.\n");
    AI("stable","This would be where the Knights of Solamnia " +
        "keep their horses.\n");
    AI(({"high entranceways","entranceways"}),"The only way " +
        "a tall warhorse could fit inside a stable, is if it " +
        "had high entranceways like these...\n");

    AE(VROOM + "es4", "north", 0);
    AE(VROOM + "stable1", "east", CAV_CLOSED);
    AE(VROOM + "ss6", "south", 0);
}
