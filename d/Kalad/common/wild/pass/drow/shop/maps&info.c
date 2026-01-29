/* A map/information shop */
/* by Antharanos */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A map/information shop");
   set_long("A map/information shop.\n");
   add_exit(CPASS(drow/d11),"south",0,-1,-1);
   set_noshow_obvious(1);
}
