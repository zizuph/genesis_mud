/* File:          /d/Khalakhor/cobhan/goblincave/cave1.c
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
    add_my_desc("Goblin cave entrance. \n");

    add_exit(GOBCAVE + "cave2", "west");
    add_exit(NROAD + "nroad2", "east", "@@enter_road", 2);
}

