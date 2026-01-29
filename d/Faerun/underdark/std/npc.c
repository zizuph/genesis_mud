/*
 * Base file for Underdark npcs
 */
 
#include "/d/Faerun/defs.h"
#include "/d/Faerun/underdark/defs.h"

inherit (FAERUN_STD + "faerun_npc");

public void
create_underdark_npc(void)
{
}

nomask public void
create_faerun_npc(void)
{
    create_underdark_npc();
}
