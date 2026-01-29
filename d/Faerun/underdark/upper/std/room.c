/*
 * Base file for rooms in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "room");

public void
create_upperdark_room(void)
{
}

nomask public void
create_underdark_room(void)
{
    // Set the defaults for these rooms
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
    // Call the general upperdark constructor
    create_upperdark_room();
}
