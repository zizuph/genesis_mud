/*
 * Base file for Underdark weapons
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/underdark/defs.h"

// inherit (P_FAERUN_STD + "faerun_weapon");
inherit (FAERUN_STD + "faerun_weapon");

public void
create_underdark_weapon(void)
{
}

nomask public void
create_faerun_weapon(void)
{
    create_underdark_weapon();
}
