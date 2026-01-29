/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"


object guard;

void
create_dunlending()
{
    set_short("Along the path");
    set_long("You stand between two wheat fields. The wheat is tall and golden "
        + "but also choked by weeds. The path you're on is thin and nothing "
        + "more than just a well-worn trail. Southeast of here is an ancient "
        + "forest full of tall trees. To the northwest is a farm, but it looks "
        + "like it's seen better days.\n");



    add_exit("/d/Gondor/rohan/farm/farm/path3", "northwest");
    add_exit(CAMP_ROOM_DIR + "p2", "east", 0, 0, 0);

    path_adds();
    add_guard_down();
}
void
reset_room()
{
    set_searched(0);
}

void
init()
{
    ::init();
    if (interactive(this_player()))
        catch(call_other("/d/Gondor/rohan/farm/farm/camp/npc/clone_handler.c", "??"));
}

