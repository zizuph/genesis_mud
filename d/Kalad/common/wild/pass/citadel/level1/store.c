inherit "/d/Kalad/room_std";
inherit "/lib/store_support";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   set_short("Store room");
   set_long("You are inside some barrels!\n");
   add_exit(CPASS(citadel/level1/a4),"southwest",0,-1);
}
public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
