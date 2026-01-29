/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
 
void
create_path_room()
{
    set_areadesc("light");
    set_area("path east of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("You stand in a clearing at the edge of the Old " +
        "Forest and the Downs. A grassy path wanders through the " +
        "clearing and around a small cottage and zig zags northeast " +
        "out of the clearing. The clearing is empty of all trees " +
        "except for a tall oak that grows on the other side of " +
        "the clearing.");

    add_exit(ROOMS_DIR + "path07", "south");
    add_exit(ROOMS_DIR + "path02", "west");
    add_exit(VAL_DIR + "val01", "northeast");


}
