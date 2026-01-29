inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_S_DARK_LONG,"A dark and moist place.\n");
   set_short("A dark tunnelway");
   set_long("This is a damp tunnelway located somewhere underneath the "+
      "spring in the rock plains above you. Some of the water from above "+
      "has leaked down here and has created a rather moist and cool "+
      "environment. Several mosses can be seen growing all over this "+
      "tunnel, which heads to the north and south.\n");
   add_item(({"damp tunnelway","tunnelway","tunnel"}),
      "A moisture-ridden underground passage.\n");
   add_item(({"water"}),
      "Surprisingly cool, it has created a moist cool environment here "+
      "where mosses can grow.\n");
   add_item(({"mosses","moss"}),
      "Green and clammy to the touch, they cover the walls and ceiling of "+
      "this tunnel.\n");
   add_item(({"walls","wall","ceiling","floor","ground"}),
      "The interior of this passage is composed of an extremely dense, "+
      "black rock, quite dissimilar to the composition of the many rocks "+
      "that lie on the rock plains above.\n");
   add_exit(CPASS(desert/rock/l3),"north","@@lamia_block");
   add_exit(CPASS(desert/rock/l1),"south");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/lamia));
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/lamia));
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"A pair of feline lamias emerge from the darkness.\n");
   }
}
lamia_block()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Lamia")
         {
         pres = 1;
        }
   }
   if(pres == 1)
      {
      write("The feline lamia prevents you from going that way!\n");
      say("The feline lamia prevents " + QTNAME(TP) + " from going north!\n");
   }
   return pres;
}
