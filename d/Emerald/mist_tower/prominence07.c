#include "defs.h"

inherit MIST_PROMINENCE_BASE;

public void
create_prominence_room()
{
    add_exit("prominence09", "northeast");
    add_exit("prominence04", "south");
}
