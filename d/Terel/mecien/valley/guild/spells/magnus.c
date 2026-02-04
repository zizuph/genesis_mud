/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define CAST_LIMIT    80   /* The limit for this to become a success */
#define TP            this_player()
#define ETP           environment(TP)
#define STD_RET       return "To whom shall this power be called?.\n"

/* Function name: magnus
* Description:   grants temporary discipline
* Arguments:     str - 
* Returns:       1/0
*/
nomask mixed
magnus(string str)
{
   object *ob, who=0, chalice;
   int mana_limit, sum;
   int ds, dt;
   
   if (str) {
      if (parse_command(str, ETP, " %l ", ob)) {
         if (sizeof(ob) >= 2) {
            if (CAN_SEE(TP, ob[1])) {
                who = ob[1];
            }
         }
      }
   }
   if (!who) {
      if (!str || str == "me" || str == "myself")
         who = TP;
      else
         STD_RET;
   }
   
   if (NPMAGIC(who))
      return "Something blocks the Ancient Power.\n";
   
   mana_limit = 50;
   if (who == TP) /* Costs more on yourself */
      mana_limit = 70;
   
   if (TP->query_mana() < mana_limit)
      return "You are too weak to attempt this.\n";
   
   chalice = present(MYSTIC_CHALICE, TP);
   if (!chalice)
      return "You need the sacred chalice for this prayer.\n";

   if (random(TP->query_skill(SS_ELEMENT_LIFE) +
              TP->query_skill(SS_FORM_ENCHANTMENT)) < random(CAST_LIMIT))
   {
      TP->add_mana(-mana_limit/3);
      return "Your call is not heard.\n";
   }
   
   TP->add_mana(-mana_limit);
   say("Holding aloft a chalice, " + QTNAME(TP) + 
       " invokes a power of mystery.\n");
   if (who == TP) {
      write("You place your lips to the sacred chalice.\n");
      say(QCTNAME(TP) + " places the chalice to " +
          TP->query_possessive() + " mouth.\n");
   } else {
      TP->catch_msg("You lower the chalice to " + QTNAME(who) +
                 " and touch it to " + who->query_possessive() +
                 " lips.\n");
      who->catch_msg(QCTNAME(TP) +
                 " lowers the chalice and touches it to your lips.\n");
      tell_room(ETP, QCTNAME(TP) +
                 " lowers the chalice and touches it to " +
                 QTNAME(who) + ".\n", ({TP, who}));
   }
   ds = 1 + random(10) + (TP->query_stat(SS_WIS))/15;
   dt = 10 + (TP->query_stat(SS_WIS))/20;
   who->add_tmp_stat(SS_DIS, ds, dt);
   who->add_tmp_stat(SS_DEX, ds, dt);
   who->add_tmp_stat(SS_STR, ds, dt);
   who->add_tmp_stat(SS_INT, ds, dt);
   who->add_tmp_stat(SS_CON, ds, dt);
   who->catch_msg("A powerful spirit of majesty descends upon you!\n");

   return 1;
}
