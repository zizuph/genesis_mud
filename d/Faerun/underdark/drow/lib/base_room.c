/*
 * Base file for rooms in upper area of Underdark
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ROOM_BASE;


nomask public void
create_faerun_room(void)
{
    // Set the defaults for these rooms
    set_faerun_region("upperdark");
    set_faerun_level(FL_UPPERDARK);
}
