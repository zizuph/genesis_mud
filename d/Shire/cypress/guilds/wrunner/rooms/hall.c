/*
 * Training room of the Wild Elves Guild
 * By Finwe, May 2001
 */
 
#pragma strict_types

#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

inherit "/d/Shire/cypress/guilds/wrunner/base_common_inside";


void
create_room()
{
    set_short("An exquisite hallway");
    set_long("This hallway is plain yet exquisite in its " +
        "simplicity. Three wings lead off to the east, west, " +
        "and southwest to various other areas of the guild. An " +
        "exit leads south outside. \n");
    set_add_column_bldg();


    add_exit(ROOM_DIR + "join",     "north");
    add_exit(ROOM_DIR + "board",   "east");
    add_exit(ROOM_DIR + "train",    "west");
    add_exit(ROOM_DIR + "start_rm", "southwest");
    add_exit(ROOM_DIR + "garden",   "south");

}
