#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem7", "north");
    add_exit("elem3", "southwest");
    add_exit("air", "west");
}
