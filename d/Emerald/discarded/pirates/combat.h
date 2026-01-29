/* This file is intended to have some nice combat help functions. */

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <filter_funs.h>

#include "/d/Emerald/defs.h"
#define PIR_I_INSULT   "k_pir_i_insult"
#define PIR_I_HOOK  "k_pir_i_hook"
#define HOOK_HIT   2500
#define SS_INSULT  70005
#define SS_HOOK    70006
#define F_HOOK_HIT(ob, ob2) ob->query_stat(SS_DEX) *\
ob->query_skill(SS_HOOK)
#define F_HOOK_PEN(ob, ob2) F_PENMOD(ob->query_stat(SS_STR),\
   17*(ob->query_skill(SS_HOOK)/10)+30)


/*
* Tests if and object can attack another
   */
string
c_can_attack(object ob, string verb)
{
   if (!ob || !living(ob) || (ob == TP))
      return CAP(verb) + " who?\n";
   
   if (ob->query_prop(OBJ_I_NO_ATTACK))
      return "You sence a divine presence protecting the intended victim.\n";
   
   if(environment(ob) && environment(ob)->query_prop(ROOM_I_NO_ATTACK))
      return "Your senses detect a magical peace spell over the room.\n";
   
   if (!TP->query_npc() && TP->query_met(ob) &&
         TP->query_prop(LIVE_O_LAST_KILL) != ob)
   {
      TP->catch_msg("Attack " + QTNAME(ob) +
         "?!? Please confirm by trying again.\n");
      TP->add_prop(LIVE_O_LAST_KILL, ob);
      return "";
   }
   
   if (!F_DARE_ATTACK(TP, ob))
      return "You don't dare to attack.\n";
}

/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send
*/
static void
tell_watcher(string str, object me, object enemy)
{
   object *ob;
   int i;
   
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}
