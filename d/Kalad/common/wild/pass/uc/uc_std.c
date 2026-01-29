inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_noshow_obvious(1);
}
void
init()
{
   ::init();
   AA(time,time);
}
time()
{
   write("It is impossible to tell, since you are far beneath the surface "+
      "of Kalad.\n");
   return 1;
}
string
query_time_desc()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->query_prop(OBJ_I_LIGHT) > 0)
      return "Your light-source barely seems to penetrate the darkness here.\n";
   else
      return "Visibility is extremely poor here, for total darkness lies but "+
   "a short distance away.\n";
}
