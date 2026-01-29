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
    set_long("This hallway is plain yet exquisite in it " +
        "simplicity. Three wings lead off to the east, west, " +
        "and southwest to various other areas of the guild. An " +
        "exit leads south, out to a private garden.\n");
    set_add_column_bldg();

    add_exit(WRUNNER_DIR + "join",     "north");
    add_exit(WRUNNER_DIR + "boards",   "east");
    add_exit(WRUNNER_DIR + "train",    "west");
    add_exit(WRUNNER_DIR + "start_rm", "southwest");
    add_exit(WRUNNER_DIR + "garden",   "out");

}