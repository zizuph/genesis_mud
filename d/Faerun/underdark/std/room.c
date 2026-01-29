/*
 * Base file for Underdark rooms
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/underdark/defs.h"

#include <stdproperties.h>

inherit (FAERUN_STD + "faerun_room");

public void
create_underdark_room(void)
{
}

nomask public void
create_faerun_room(void)
{
    remove_prop(ROOM_I_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);

    create_underdark_room();
}
