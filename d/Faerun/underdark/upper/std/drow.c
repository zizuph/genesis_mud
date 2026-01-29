/*
 * Base file for Drow in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "drow");

public void
create_upperdark_drow(void)
{
}

nomask public void
create_underdark_drow(void)
{
    // Set the defaults for these rooms
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
    // Call the general upperdark constructor
    create_upperdark_drow();
}
