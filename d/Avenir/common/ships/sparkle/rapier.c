// -*-C++-*-
// name: Rapier  ~Avenir/common/ships/sparkle/rapier.c
// creator(s):   Tepisch  Nov 1994
// last update:  Boriska, Mar 23 1995
// purpose:      To be wielded by captain
// note:         Rogon's "continuos-alarms" doc in ~rogon/open was helpful
//               in determining the (I hope) proper use of *_alarm.
// bug(s):
// to-do:

#pragma save_binary

inherit "/std/weapon";

#include "../ship.h"
#include <formulas.h>
#include <wa_types.h>

#define ETO     environment(this_object())
#define F_GAIN  50

int alarm_id;

void
create_weapon() 
{
   set_name("rapier");
   set_short("elegant rapier");
   set_pname("rapiers");
   set_pshort("elegant rapiers");
   set_adj("elegant");
   LONG("This is narrow blade is long and slightly flexible.\n"+
        "It is so light in the hand that wielding it for long periods "+
        "is unlikely to cause fatigue.\n");
   set_hit(30);
   set_pen(20);
   set_wf(TO);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);

   add_prop(MAGIC_AM_MAGIC, ({ 30, "life" }));
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_ID_INFO,
	({ "The rapier appears to be magical.\n", 1,
           "The rapier is magically light-weight and balanced.\n", 30,
	   "It will energize the wielder, reducing fatigue.\n", 60 }));
   add_prop(OBJ_S_WIZINFO, "A magically lightweight and balanced "+
       "rapier that adds 10 fatigue points every minute while wielded.\n"+
       "   Wielded by: Staek (/d/Avenir/common/ships/sparkle/captain)\n"+
       "   Cloned at: (/d/Avenir/common/ships/sparkle/ship)\n");
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,20) + random(250));

}


#if 0
// special stuff disabled by Boriska
// this alarm is wasteful
int
wield(object ob)
{
  if (ETO == TP)
    alarm_id = set_alarm(70.0, 60.0,"do_boost");
  return 0;
}

int
unwield()
{
  remove_alarm(alarm_id);
  return 0;
}

void                                                                          
do_boost()                                                                    
{      
    object wielder = query_wielded();           
    if ((wielder->query_prop(MAGIC_I_RES_ELECTRICITY)) ||
	(wielder->query_prop(OBJ_I_RES_ELECTRICITY)))
      return;                                                                
    
    if (TO->query_prop(OBJ_I_BROKEN))                                         
      {
	remove_alarm(alarm_id);                                               
        return;                                                               
      }
    
    
   wielder->catch_msg("\nA vague electrical tingling rises from the hand wielding "+
      "the elegant rapier and flows over you like a cool breeze.\n"+          
      "You feel refreshed and invigorated, less tired.\n");                   
   wielder->add_fatigue(F_GAIN);
   return;                                                                    
}                
#endif
