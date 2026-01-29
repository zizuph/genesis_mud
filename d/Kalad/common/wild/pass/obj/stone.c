inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>

   create_object()
{
   set_name("stone");
   set_long("This is a small piece of rock.\n");
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
}
init()
{
   add_action("throw_me","throw");
}
throw_me(string s)
{
   object bum;
   string dir;
   
   NF("Throw what where?\n");
   if(!parse_command(s,E(TO),"%o %w",bum,dir))
      return 0;
   
   say(QCTNAME(TP)+" throws a stone to the "+dir+"\n");
   write("You throw the stone "+dir+".\n");
   
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
      tell_room(E(TO),"The stone hits an obstacle, and falls to the ground in a very unflattering way.\n");
      return 1;
   }
   
   where = E(TO)->query_exit()[i-1];
   tell_room(where,"A stone flies through the air, heading "+dir+".\n");
   TO->move(where);
   
   apa = FILTER_LIVE(all_inventory(E(TO)));
   
   if((i = random(7))<sizeof(apa))
      {
      apa[i]->catch_msg("You get hit in the head by the stone.\n");
      
      tell_room(E(TO),QCTNAME(apa[i])+" gets hit in the head by the stone.\n");
#ifdef THIS_IS_RIDICULOUS
      apa[i]->heal_hp(-(apa[i]->query_hp()/20));
#else
      apa[i]->hit_me(5, W_BLUDGEON, this_player(), -1, A_HEAD);
#endif
      return 1;
   }
   set_alarm(0.5,0.0,"throw_it",dir);
   
   return 1;
}

