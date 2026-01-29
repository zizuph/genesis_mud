#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem8", "north");
    add_exit("elem4", "south");
    add_exit("trial1", "west");
}
