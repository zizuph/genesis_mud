#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem12", "northwest");
    add_exit("elem7", "south");
    add_exit("water", "west");
}
