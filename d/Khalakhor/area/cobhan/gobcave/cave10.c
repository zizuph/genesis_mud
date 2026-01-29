/* File:          /d/Khalakhor/cobhan/goblincave/cave10.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a goblin cave room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "gobcave_base";

public void
reset_gobcave_room()
{
}

public void
create_gobcave_room()
{
    set_up_gobcave();
    set_long("@@my_long");
    add_my_desc("Goblin cave. \n");

    add_exit(GOBCAVE + "cave8", "east");
}

