#include "defs.h"

inherit MIST_PROMINENCE_BASE;

public void
create_prominence_room()
{
    add_exit("prominence01", "west");
    add_exit("prominence05", "northeast");
}
