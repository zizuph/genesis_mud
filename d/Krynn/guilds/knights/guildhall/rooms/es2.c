/* East street 2, VK
 * By Teth, Dec. 3 1996
 */


#include "../../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("To the east is a building, with a closed door. " +
        "The street continues to the north and south.\n");
    AI(({"door","closed door"}),"The door appears to be boarded shut.\n");
    AE(VROOM + "es1", "north", 0);
    AE(VROOM + "farrier_store","east", "@@closed", 0);
    AE(VROOM + "es3", "south", 0);
}

int
closed()
{
    write("As hard as you try to go through the door, it doesn't " +
        "budge. Using your common sense, you figure that perhaps " +
        "this will be a farrier's store one day.\n");
    return 1;
}
