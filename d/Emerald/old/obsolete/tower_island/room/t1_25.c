#include "../defs.h"

inherit T1_OUT_BASE;

nomask void
create_t1_room()
{
    add_shore();

    add_exit("t1_22", "northwest");
    add_exit("t1_24", "west");
}
