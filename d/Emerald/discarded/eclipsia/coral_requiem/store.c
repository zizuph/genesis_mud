 
inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h> 
#include "../edefs.h"
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
 
void
create_room()
{
    set_short("Coral Requiem General Store store room");
    set_long("This is the store room for the Coral Requiem " +
        "general store.  Only wizards are allowed in here.\n");

    add_exit(CRDIR + "shop", "west");
 
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
 
}
