#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("air", "north");
    add_exit("elem5", "northeast");
    add_exit("elem2", "west");
}
