#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("fire", "north");
    add_exit("elem2", "east");
    add_exit("elem4", "northwest");
}
