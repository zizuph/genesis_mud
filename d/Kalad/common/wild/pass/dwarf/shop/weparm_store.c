inherit "/d/Kalad/room_std";
inherit "/lib/store_support";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   set_short("Store room");
   set_long("You are in the store room of Underhome's weapon and "+
      "armour shop.\n");
   add_exit(CPASS(dwarf/shop/weparm_shop),"east",0,-1,-1);
}
public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
