inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int pres,i;
object *ob;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("Entrance room of the Merchants Guild");
   set_long("The entrance room of the Merchants Guild of Kabal.\n");
   add_exit(CVAN(wayfar/s2),"north",0,-1,-1);
   add_exit(CVAN(guild/joinroom),"south","@@check_move",-1,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CGUILDS(merchant/entrance_guard));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A guardsman arrives at his post.\n");
   }
}
check_move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Erdellar")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("You are prevented from going south by the entrance guardsman.\n");
      say(QCTNAME(TP) + " tried to go south but was stopped by the entrance guardsman.\n");
   }
   return pres;
}
