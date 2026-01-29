inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("within a smith in Underhome");
   set_long("All around you, you see piles of weapons and "+
      "armours that all look like brand "+
      "new. Not a drop of blood has touched them yet.\n");
   
   add_exit(CPASS(dwarf/smith/s1),"northwest",0,-1,-1);
   set_alarm(2.0,0.0,"reset_room");
   
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/wep/miner_axe));
      ob1->move(TO);
      tell_room(TO,"A deep dwarf enters the room and drops a newmade axe.\n");
   }
}
