/*
 * Base file for Underdark armours
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/underdark/defs.h"

inherit (FAERUN_STD + "faerun_armour");

public void
create_underdark_armour(void)
{
}

nomask public void
create_faerun_armour(void)
{
    create_underdark_armour();
}
