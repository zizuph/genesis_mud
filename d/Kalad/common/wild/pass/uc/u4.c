inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define DG "/d/Kalad/common/wild/pass/uc/npc/drow_guard"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A somewhat narrow passage");
   set_long("You are at a somewhat narrow passage.\n"+
      "Rock as dark as the lightless depths of the netherworld surround "+
      "you, enclosing you with its cold, hard embrace. The sheer weight of "+
      "stone overhead seems to absorb the very strength from your form, "+
      "leaving you weak and weary. The passage continues on to the north "+
      "and south, while a side passage leads to the west.\n"+
      "Beyond lies darkness.\n");
   add_item(({"passage"}),
      "Which passage?\n");
   add_item(({"somewhat narrow passage","narrow passage"}),
      "A cramped tunnel far beneath the surface of Kalad.\n");
   add_item(({"side passage","smaller passage"}),
      "A smaller, side passage that heads west from here.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u3),"west",0,2,1);
   add_exit(CPASS(uc/u2),"north","@@check",2,1);
   add_exit(CPASS(uc/u5),"south",0,2,1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(DG);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(DG);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"Some figures emerge from the darkness.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Drow")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The drow blocks your way!\n");
      say("The drow prevents " + QTNAME(TP) + " from going north.\n");
   }
   return pres;
}
