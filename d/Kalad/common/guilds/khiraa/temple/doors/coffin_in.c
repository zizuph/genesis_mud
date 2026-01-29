#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"coffin lid","lid"}));
    set_door_desc("It is the coffin lid. You could perhaps open "+
    "and get out with 'exit'.\n");
    set_pass_command(({"exit coffin","exit","leave","leave coffin"}));
    set_door_id("khiraa_coffin");
    set_other_room(KHIRAA_DIR(temple/rooms/temple_join));
    set_open(0);
}
    
int
open_door(string arg)
{
    ::open_door(arg);
    return 1;
}
