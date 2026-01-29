#include "defs.h"

inherit MIST_PROMINENCE_BASE;

public void
create_prominence_room()
{
    add_exit("prominence06", "east");
    add_exit("prominence02", "southwest");
}
