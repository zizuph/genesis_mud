/*
 * Base file for Drow elves
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/underdark/defs.h"

inherit (FAERUN_STD + "drow_npc");

public void
create_underdark_drow(void)
{
}

nomask public void
create_faerun_drow(void)
{
    create_underdark_drow();
}
