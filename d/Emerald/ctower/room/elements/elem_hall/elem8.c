#include "../../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
    add_exit("elem10", "northeast");
    add_exit("elem6", "south");
    add_exit("earth", "east");
}
