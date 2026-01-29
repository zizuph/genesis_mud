#include "default.h"

inherit PATH_BASE;

void
create_path()
{
    add_exit("path1", "south", 0, 4);
    add_exit("path3", "northwest", 0, 6);
}
