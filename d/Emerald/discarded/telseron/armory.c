inherit "/std/room";
inherit "/lib/store_support";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Armory");
    set_long("This is the armory where all the weapons and armours are kept.\n");
 
    set_max_values(30, 3);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "armorer", "east", 0);
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
