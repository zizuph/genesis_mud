#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"black gold-runed door","door","north door"}));
    set_door_desc("It is an old door made of black oak. On it, "+
    "you see many beautiful gold runes and decorations. In "+
    "the very center is a S shaped symbol crossed by a large "+
    "skull-topped staff.\n");
    set_pass_command(({"n","north"}));
    set_door_id("shrinedoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t12));
    set_open(0);
}
    
