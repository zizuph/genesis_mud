/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <cmdparse.h>
#include "spells.h"
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP         this_player()
#define ETP        environment(TP)

/* Function name: beatus
* Description:   gives target a blessing
* Arguments:     str - who or what
* Returns:       1/0
*/
nomask mixed
beatus(string str)
{
   object who, *ob;
   int mana_limit, sum;
   string arg;

   if (!str) return "Who or what shall you bless?\n";

   arg = str;
   if (str == "me" || str == "myself") arg = TP->query_real_name();

   ob = FIND_STR_IN_OBJECT(arg, ETP);
   if (sizeof(ob) == 0) ob = FIND_STR_IN_OBJECT(arg, TP);
   if (sizeof(ob) == 0 || sizeof(ob) >= 2)
      return "Who or what shall you bless?\n";

   who = ob[0];
   if (!CAN_SEE(TP, who)) return "Who or what shall you bless?\n";

   if (NPMAGIC(who))
      return "Something prevents you from cast this spell.\n";

   if (who->query_prop(MYSTIC_BLESSED) &&
       who->query_skill(CURSED) == 0)
   {
      if (who == TP) {
         TP->catch_msg("You are already blessed!\n");
       } else {
         if (living(who)) {
            TP->catch_msg(QCTNAME(who) + " is already blessed!\n");
            } else {
            TP->catch_msg("The " + who->short() +
               " is already blessed!\n");
            }
       }
      return 1;
   }

   if (who == TP) /* Costs more to heal yourself */
      mana_limit = BEATUS_SELF_MANA;
   else
      mana_limit = BEATUS_OTHER_MANA;

   if (TP->query_mana() < mana_limit)
      return "You do not have the strength to call out.\n";

   if (random(TP->query_skill(SS_FORM_ENCHANTMENT) +
            TP->query_stat(SS_WIS)) < random(BEATUS_CAST_LIMIT))
   {
      write("Your call is not heard.\n");
      TP->add_mana(-mana_limit / 3);
      return 1;
   }

   TP->add_mana(-mana_limit);

   if (who == TP) {
      write("You call the blessing of the Ancients " +
         "down upon yourself.\n");
      say(QCTNAME(TP) + " prays silently.\n");
      write("A divine power touches you.\n");
      who->add_prop(MYSTIC_BLESSED, 1);
      return 1;
   }

   if (living(who)) {
      TP->catch_msg("You invoke the blessings of the Ancients upon " +
         QTNAME(who) + ".\n");
      say(QCTNAME(TP) + " prays over " + QTNAME(who) + ".\n",
         ({who, TP}));
      who->catch_msg("A divine power gently touches you.\n");
      who->catch_msg("You have been blessed by "+QTNAME(TP)+".\n");
      if (who->query_skill(CURSED) > 0) {
          TP->catch_msg(QCTNAME(who) + " is no longer cursed.\n");
          who->catch_msg("You are no longer cursed by the Ancients.\n");
      }
      who->remove_skill(CURSED);
      if (present(MYSTIC_BEADS, who)) {
         TP->catch_msg(QCTNAME(who) + " is now a chosen seeker.\n");
         who->set_skill(BLESSED, 1);
         who->catch_msg("You feel you have been chosen.\n");
      }
   } else {
      write("You invoke the blessings of the Ancients upon the " +
            who->short() + ".\n");
      say(QCTNAME(TP) + " prays over the " + who->short() + ".\n");
   }
   who->add_prop(MYSTIC_BLESSED, 1);
   return 1;
}
