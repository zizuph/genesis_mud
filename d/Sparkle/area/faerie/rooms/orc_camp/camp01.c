/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A path leads northwest out of the camp.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();

    set_short("A dirty path in an orc camp");
    set_long(camp_desc1(extra_line));

    add_exit(OC_DIR + "camp05", "south");
    add_exit(OC_DIR + "camp02", "east");
    add_exit(FOREST_DIR + "path04", "northwest");
    add_exit(OC_DIR + "camp04", "southwest");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SOLDIER, NO);
}
