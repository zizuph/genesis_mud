/*
 * Base file for npcs in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "npc");

public void
create_upperdark_npc(void)
{
}

nomask public void
create_underdark_npc(void)
{
    // Set the defaults for these rooms
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
    // Call the general upperdark constructor
    create_upperdark_npc();
}
