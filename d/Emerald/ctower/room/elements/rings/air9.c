#include "../../../ctower.h"

inherit AIRSTD;
 
void
create_air()
{
    add_exit("air8", "northeast");
    add_exit("air10", "northwest");
    add_exit("earth1", "north");
    add_exit("guard3", "up");
}
