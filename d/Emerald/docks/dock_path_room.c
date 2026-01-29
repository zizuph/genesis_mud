#include "defs.h"

inherit CERAL_ROOM;

void
create_dock_path_room()
{
}

nomask void
create_ceral_room()
{
    set_em_long("A circular pathway leads around the small island, " +
        "providing access to the many docks.  Inside the circle, " +
        "you can see a large pavilion.\n");

    create_dock_path_room();
}

public int
dock_block()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    write("The other docks have been closed by order of the King; thus, " +
        "the pathway is blocked in that direction.\n");
    return 1;
}

public int
cargo_dock_block(string dir)
{
    write("The dock to the " + dir + " is for cargo ships only. " +
        "Passengers are not permitted in the unloading area.\n");
    return 1;
}

public void
add_cargo_dock_exit(string dir)
{
    add_exit("", dir, &cargo_dock_block(dir));
}

public void
add_dock_map()
{
    add_my_desc("A map of the area is posted here.\n");

    setuid();
    seteuid(getuid());

    /* We store the map in a separate file.  This makes editing easier */
    add_item("map", read_file(DOCK_DIR + "MAP.public"));
}
