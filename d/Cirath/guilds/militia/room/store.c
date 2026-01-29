inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Cirath/common/defs.h"
#include "../defs.h"

void
create_room()
{
    set_short("Storage Room");
    set_long("This is the room where members may store weapons and "
    	+"other equipment after a day of adventuring.  The faint "
    	+"smell of blood lingers in this room, as if some of this "
    	+"equipment has been used quite frequently.  Militias are "
    	+"not given weapons that are that nice usually, and anything "
    	+"left here is a welcome addition to the arsenal.\n");
    add_exit(MILITIA_ROOM + "startroom","west");
    add_exit(MILITIA_ROOM + "m10","north");
    reset_room();
}

