/*
 * Downstairs west hall of Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("The upstairs hallway");
    set_long("This is the upstairs hallway. It's plain like the " +
        "others with a large window set into the east wall. " +
        "The floor is bare except for a large carpet. A staircase " +
        "leads downstairs. Lamps hanging from the ceiling fill " +
        "the room with soft light.\n");
    add_item(({"carpet"}),
        "The carpet is long and rectangular. It is a soft blue " +
        "color with abstract flower designs. The ends of the carpet " +
        "have a white fringe.\n");
    add_item(({"flower designs", "abstract flower designs", "designs"}),
        "Abstract birds in flight decorate the carpet.\n");
    set_add_staircase("The staircase leads downstairs.");

    reset_shire_room();


    add_item(({"east window", "eastern window"}), 
        "@@east_up@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "east wall.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
    num_of_windows=1;

    add_exit(ROOMS_DIR + "rm_sewing",    "north");
    add_exit(ROOMS_DIR + "rm_bdrm",   "west");
    add_exit(ROOMS_DIR + "rm_hall02", "down");
}
void
init()
{
    ::init();
}


void
reset_shire_room()
{
}
