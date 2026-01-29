inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("rock");
   set_adj("large");
   set_long("A large two foot wide rock, virtually a small boulder.\n");
   add_prop(OBJ_I_WEIGHT,25000);
   add_prop(OBJ_I_VOLUME,25000);
}
init()
{
   add_action("throw_me","throw");
}
throw_me(string s)
{
   object bum;
   string dir;
   
   NF("You are not strong enough!\n");
   if(TP->query_stat(SS_STR) < 76)
      return 0;
   NF("You are not skilled enough!\n");
   if(TP->query_skill(SS_WEP_MISSILE) < 11)
      return 0;
   NF("Throw what where?\n");
   if(!parse_command(s,E(TO),"%o %w",bum,dir))
      return 0;
   
   say(QCTNAME(TP) + " throws a large rock " + dir + ".\n");
   write("You throw the large rock "+dir+".\n");
   
   TO->move(E(TP));
   return(bum->throw_it(dir));
}
throw_it(string dir)
{
   string where;
   
   int i;
   object *apa;
   
   if((i=member_array(dir,E(TO)->query_exit()))<0)
      {
      tell_room(E(TO),"A large rock comes crashing to the ground.\n");
      set_alarm(1.0,0.0,"remove_rock");
      return 1;
   }
   
   where = E(TO)->query_exit()[i-1];
   tell_room(where,"A large rock flies through the air, heading "+dir+".\n");
   TO->move(where);
   
   apa = FILTER_LIVE(all_inventory(E(TO)));
   
   if((i = random(3))<sizeof(apa))
      {
      apa[i]->catch_msg("You get hit in the head by a large rock!\n");
      
      tell_room(E(TO),QCTNAME(apa[i]) + " got hit in the head by a large rock!\n");
      apa[i]->heal_hp(-500);
      set_alarm(1.0,0.0,"remove_rock");
      return 1;
   }
   set_alarm(0.5,0.0,"throw_it",dir);
   
   return 1;
}
remove_rock(int i)
{
   if(i == 0)
      {
      tell_room(E(TO),"The large rock crumbles to dust upon impact.\n");
      remove_object();
   }
   else
      set_alarm(3.0,itof(i-1),"remove_rock");
}
