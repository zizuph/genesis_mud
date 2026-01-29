#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"eerie wooden coffin","coffin"}));
    set_door_desc("A coffin, about normal human height. It "+
    "is made of black polished wood, and looks rather eerie. "+
    "A red grim-looking skull has been painted on its lid. "+
    "If you wanted to enter it, 'coffin' would work nicely.\n");
    set_pass_command(({"enter coffin","coffin"}));
    set_door_id("khiraa_coffin");
    set_other_room(KHIRAA_DIR(temple/rooms/dark_coffin));
    set_open(0);
}
    
