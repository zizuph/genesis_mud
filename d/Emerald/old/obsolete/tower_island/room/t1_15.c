#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_cell();

    add_exit("t1_12", "northeast");
}
