/*
 * Base file for weapons in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"


inherit (UNDER_STD_DIR + "wep");

public void
create_upperdark_weapon(void)
{
}

nomask public void
create_underdark_weapon(void)
{
    // Set the defaults for these weapons
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
    // Call the general upperdark constructor
    create_upperdark_weapon();
}
