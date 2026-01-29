/* File:          /d/Khalakhor/cobhan/dwarfcave/cave1.c
 * Creator:       Teth
 * Date:          Dec 25 2001
 * Modifications:
 * Purpose:       This is a dwarf cave room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "dwarfcave_base";

public void
reset_dwarfcave_room()
{
}

public void
create_dwarfcave_room()
{
    set_up_dwarfcave();
    set_long("@@my_long");

    add_my_desc("Dwarf cavern. \n");

    add_exit(SROAD + "sroad3", "north", "@@enter_road");
    add_exit(DWARFCAVE + "cave5", "southeast");
    add_exit(DWARFCAVE + "cave4", "south");
    add_exit(DWARFCAVE + "cave2", "southwest");
}

