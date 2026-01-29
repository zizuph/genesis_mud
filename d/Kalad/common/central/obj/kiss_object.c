inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>

object ring_bearer;

void
create_object()
{
   ::create_object();
   set_name("kiss_object");
   set_long("an invisible object that gives the player a command.\n");
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_INVIS, 99);
   add_prop(OBJ_I_NO_DROP,1);
   set_alarm(10.0,0.0,"kill_me");
}

set_ring_bearer(object who)
{
   if (who) ring_bearer=who;
}

init()
{
   ::init();
   add_action("kiss","kiss");
}

kiss(string what)
{
   int is_here;
   object *ob;
   int i;
   is_here = 0;
   ob = FILTER_LIVE(all_inventory(E(TP)));
   for (i=0;i<sizeof(ob);i++)
   {
      if(ring_bearer->query_real_name()==ob[i]->query_real_name())
         is_here=1;
   }
   if (!is_here)
      {
      say("did not find ring_bearer\n");
      remove_object();
      return 0;
   }
   notify_fail("Kiss what?\n");
   if (!what || what!="ring") return 0;
   
   write("You place yourself on one knee and kiss the ring, showing "+
      "your respect to "+C(ring_bearer->query_real_name())+".\n");
   say(QCTNAME(TP)+" places "+TP->query_objective()+"self on one knee "+
      "and kisses the ring offered by "+QTNAME(ring_bearer)+
      ".\n",({ ring_bearer, TP }));
   ring_bearer->catch_msg(QCTNAME(TP)+" lowers "+TP->query_objective()+
      "self on one knee and kisses the ring you offered to "+
      TP->query_objective()+".\n");
   remove_object();
   return 1;
}

kill_me()
{
   object *ob;
   int i;
   int is_here;
   is_here = 0;
   ob = FILTER_LIVE(all_inventory(E(TP)));
   for (i=0;i<sizeof(ob);i++)
   if(ring_bearer->query_real_name()==ob[i]->query_real_name())
      is_here=1;
   if (!is_here)
      {
      remove_object();
      return 0;
   }
   tell_object(E(TO),"It seems like you decided not to kiss that ring.\n");
   say(QCTNAME(E(TO))+" seems to have decided not to kiss the ring of "+
      QTNAME(ring_bearer)+".\n",({ ring_bearer, E(TO) }));
   ring_bearer->catch_msg("It seems like "+QTNAME(E(TO))+" will "+
      "not kiss your ring!\n");
   remove_object();
}
