#include "default.h"

inherit PATH_BASE;

#include "/d/Emerald/defs.h"

void
create_path()
{
    add_exit("path2", "southeast", 0, 4);
    add_exit( THIEF_LAIR_DIR + "enter", "up", 0, 6);
}
