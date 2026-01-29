/*
 * Base file for armours in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "arm");

public void
create_upperdark_armour(void)
{
}

nomask public void
create_underdark_armour(void)
{
    // Set the defaults for these armours
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
    // Call the general upperdark constructor
    create_upperdark_armour();
}
