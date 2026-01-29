#include "defs.h"
inherit STD_ROOM;
inherit "/lib/store_support";
/* by Sarr */
create_room()
{
   add_prop(ROOM_I_INSIDE,1);
   ::create_room();
   set_short("Store room");
   set_long("You are in the store room the general store in Drakmere.\n");
   add_exit("/d/Raumdor/common/drakmere/shop/gshop", "west",0);
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
