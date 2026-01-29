#include "defs.h"

inherit DOCK_PATH_ROOM;

public int     check_exit();

void
create_dock_path_room()
{
    add_exit("faerie/dock", "north", check_exit, 1, 0);
    add_exit("dock15", "southeast");
    add_exit("dock13", "west");
}


public int
check_exit()
{
    write("The northern docks have been temporarily blocked.\n");
    return 1;
}
