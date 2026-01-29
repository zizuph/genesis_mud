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
   add_prop(ROOM_S_DARK_LONG,"A dark and moist tunnel.\n");
   set_short("A dark tunnelway");
   set_long("This is a bend in a long dark tunnel that heads off to the "+
      "south and southeast. The air here is damp from the moisture of the "+
      "spring that lies several feet overhead, through the porous rocks "+
      "that compose this passage. Mosses grow rampantly in many places, no "+
      "doubt due to the presence of the water so prevalent here.\n");
   add_item(({"bend"}),
      "Its where this tunnel curves sharply, heading in different directions "+
      "to the south and southeast.\n");
   add_item(({"dark tunnelway","dark tunnel","tunnelway","tunnel"}),
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
   add_item(({"porous rocks","rocks","porous rock","rock"}),
      "The strange black rock looks to be riddled with many tiny cracks and "+
      "holes, which allow water from above to reach down here.\n");
   add_exit(CPASS(desert/rock/l5),"southeast","@@lamia_block");
   add_exit(CPASS(desert/rock/l3),"south");
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
      tell_room(TO,"Suddenly, a pair of feline lamias burst forth from the "+
         "surrounding darkness!\n");
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
      say("The feline lamia prevents " + QTNAME(TP) + " from going southeast!\n");
   }
   return pres;
}
