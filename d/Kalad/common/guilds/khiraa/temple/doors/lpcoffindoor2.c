#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"skull-shaped door","door","north door"}));
    set_door_desc("This door is shaped like a skull. Two red "+
    "eyes stare at you from within the skull's eye holes.\n");
    set_pass_command(({"n","north"}));
    set_door_id("lpcoffindoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t13));
    set_open(0);
}
    
