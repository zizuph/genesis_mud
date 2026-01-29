#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"dusty cracked door","door","south door"}));
    set_door_desc("This door looks very old and dusty. There are "+
    "some cracks on it. In the center, you see a faided picture of "+
    "a black grim-looking skull.\n");
    set_pass_command(({"s","south"}));
    set_door_id("dkcoffindoor");
    set_other_room(KHIRAA_DIR(temple/rooms/temple_dk_coffins));
    set_open(0);
}
    
