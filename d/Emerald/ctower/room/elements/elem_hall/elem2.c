#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit(CTOWER_ROOM_MAZE + "guard1", "south");
    add_exit("elem3", "east");
    add_exit("elem1", "west");
}
