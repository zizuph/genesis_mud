
/*
     This file contains some combat help functions for the 
     Zintra BlackHand Order of Assassins.

     => DONE <=                    ~Rico 12.04.96
*/

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <filter_funs.h>

#define ZINTRA_I_KICK     "_zintra_i_kick"
#define ZINTRA_I_THRUST   "_zintra_i_thrust"

/*
 * Function Name: c_can_attack
 * Description  : Tests if an object can attack another.
 */
string
c_can_attack(object ob, string verb)
{
   string mess;

   if (!ob || !living(ob) || (ob == TP))
      return C(verb) + " who?\n";

   if (mess = ob->query_prop(OBJ_M_NO_ATTACK))
      return (stringp(mess) ? mess : "You sense a divine presence "+
         "protecting your intended victim.\n");

   if (E(ob)&&(mess=E(ob)->query_prop(ROOM_M_NO_ATTACK)))
      return(stringp(mess)?mess : "You are suddenly compelled toward "+
         "peacefulnes.\n");

   if (!TP->query_npc() && TP->query_met(ob) &&
      TP->query_prop(LIVE_O_LAST_KILL) != ob)
   {
      TP->catch_msg("Attack " + QTNAME(ob) +
         "?!? Please confirm by trying again.\n");
      TP->add_prop(LIVE_O_LAST_KILL, ob);

      return "";
   }

   if (!F_DARE_ATTACK(TP, ob))
      return "You can't collect enough courage to attack.\n";
}

/*
 * Function Name: tell_watcher
 * Description  : Send the string from the fight to people that want them.
 * Arguments    : The string to send.
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

