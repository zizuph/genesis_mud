/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;

void
create_camp_room()
{
    set_short("Outside a large tent");
    set_extraline("This expanse of blue-green grass is a bit "+
        "littered with debris, such as might wash up after a "+
        "flood. A faint depression in the ground leads " +
        "northwest and east.");
    add_item(({"expanse","debris","litter"}),
        "The litter is mostly brush and other formerly living "+
        "debris, including not a few bones.\n");
    add_item("track","The track is little more than a "+
        "depression in the grass where feet have passed.\n");
  
    add_exit(CAMP_DIR + "trail2", "northwest");
    add_exit(CAMP_DIR + "track02", "east", "@@block_way@@");

    reset_shire_room();
}

void reset_shire_room()
{
    clone_invading_orcs();
}
