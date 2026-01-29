#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem6", "north");
    add_exit("fire", "east");
    add_exit("elem1", "southeast");
}
