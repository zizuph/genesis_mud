/* File:          /d/Khalakhor/cobhan/dwarfcave/cave7.c
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
    add_my_desc("This is where the nasty dwarf will be. \n");

    add_exit(DWARFCAVE + "cave6", "west");
}

