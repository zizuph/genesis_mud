/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <macros.h>
#include <std.h>

#define MANA_LIMIT    50
#define CAST_LIMIT    75  /* The limit for this to become a success */
#define NOMEN         "/d/Terel/mecien/valley/guild/archive/archive"
#define TP            this_player()
#define ETP           environment(TP)
#define ETPINV        all_inventory(ETP)
#define ENV           environment

/* Function name: oblivisci
 * Description:   mystic divines name of object/player
 * Arguments:     str - target
 * Returns:       1/0
 */
nomask mixed
oblivisci(string target)
{
   object who;
   int n, found, mana_limit, suc;
   string *names, nam, tit, myentry;

   if (!target) return "Who shall lose their mind?\n";

   if (target == "me" || target == "myself")
       who = TP;
   else
       if (!parse_command(lower_case(target), ETPINV, " %o ", who))
           return "Whom shall be disrupted?\n";

   if (!living(who))
       return "Whose mind shall we alter?\n";

   if (NPMAGIC(who))
       return "Something or somebody has blocked your power.\n";

   if (who == TP) 
       return "That is a darkness you do not wish to attempt.\n";

   mana_limit = MANA_LIMIT;

   if (TP->query_mana() < mana_limit)
      return "You are too weak to attempt this.\n";

   suc  = TP->query_skill(SS_FORM_DIVINATION);
   suc += TP->query_skill(SS_SPELLCRAFT);
   suc -= who->query_skill(SS_FORM_ABJURATION);
   if (random(suc) < random(CAST_LIMIT))
   {
       TP->add_mana(-mana_limit / 3);
       return "You were unable to disrupt the mind.\n";
   }

   if (SECURITY->query_wiz_rank(who->query_real_name()))
       return "A divine power shall never be touched.\n";

   TP->add_mana(-mana_limit);
   write("You call forth the spirits of darkness to consume your identity.\n");
   say(QCTNAME(TP) + " raises a hand and speaks some mystic words.\n");
   tell_room(ETP, "A darkness arises and swirls about like a coiling " +
             "serpent and enters the ear of " + QTNAME(who) + ".\n", who);
   who->catch_msg("A dark power touches you.\n");
   who->remove_remembered(TP->query_real_name());
   return 1;
}
