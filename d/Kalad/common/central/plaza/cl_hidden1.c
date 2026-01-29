inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 0;
   add_prop(ROOM_I_INSIDE,1);
   DIRTY(2);
   add_prop(ROOM_I_LIGHT,0);
   set_short("hidden passage");
   set_long("You travel down the dark passage.\n"+
      "You can barely see this passageway, but it does lead "+
      "northwards through a lot of cobwebs. "+
      "You can also enter the hatch.\n");
   add_item("cobweb","They hang from the walls, the ceiling, everywhere.\n");
   set_noshow_obvious(1);
   add_exit(CENTRAL(plaza/cl_hidden2),"north",0,-1);
   add_exit(CENTRAL(plaza/cl_off2),"enter",0,3);
}
