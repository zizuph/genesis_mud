#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"black silver-runed door","door","south door"}));
    set_door_desc("It is an old door made of black oak. On it, "+
    "you see many beautiful silver runes and decorations. In "+
    "the very center is a large grim skull with a dagger going "+
    "through its head.\n");
    set_pass_command(({"s","south"}));
    set_door_id("traindoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t16));
    set_open(0);
}
    
