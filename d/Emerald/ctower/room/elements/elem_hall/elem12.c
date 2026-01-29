#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem11", "west");
    add_exit("water", "south");
    add_exit("elem9", "southeast");
}
