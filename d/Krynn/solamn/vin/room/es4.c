/* East Street 4, VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("The street continues north and south, and " +
        "there is a small building to the west.\n");
    AI(({"building","small building"}),"A building that, " +
        "although small, is used very often by visitors to " +
        "Vingaard Keep. A symbol is etched near the entrance.\n");
    AI("entrance","The way into the building.\n");
    AI(({"etched symbol","symbol"}),"The symbol is of a folded " +
        "envelope, sealed with wax.\n");

    AE(VROOM + "out_post", "west", 0);
    AE(VROOM + "es3", "north", 0);
    AE(VROOM + "es5", "south", 0);
}
