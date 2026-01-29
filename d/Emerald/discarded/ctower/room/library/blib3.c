#include "../../ctower.h"
 
inherit LIBSTD;
 
void
create_lib()
{
    add_exit(CTOWER_ROOM + "blib2", "north");
    add_exit(CTOWER_ROOM + "blib1", "northeast");
}
