/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/spells/spells.h"

#define VOID    "/d/Terel/mecien/void"
#define TP      this_player()
#define ETP     environment(TP)
#define TO      this_object()

/* Function name: perditus.c
 * Description:   send target to void
 * Arguments:     str - name of victim
 * Returns:       1/0
 */
nomask mixed
perditus(string str)
{
   object who, mvoid;
   int mana_limit, suc;
   
   if (!str) return "Whom shall you condemn?\n";

   if (str == "me" || str == "myself")
      who = TP;
   else
      who = present(lower_case(str), ETP);
   
   if (!who || !living(who))
      return "Whom shall you condemn?\n";

   if (NPTELEPORT(who) || NPMATTACK(who))
      return "Something prevents that you cast this spell.\n";
   
   mana_limit = PERDITUS_MANA_COST;

   if (TP->query_mana() < mana_limit)
      return "You do not have the strength to call out.\n";
   
   suc  = random(TP->query_skill(SS_ELEMENT_DEATH));
   suc += random(TP->query_skill(SS_FORM_ABJURATION));
   suc -= random(who->query_magic_res(MAGIC_I_RES_DEATH));
    if (suc <= random(PERDITUS_CAST_LIMIT)) {
      TP->add_mana(-mana_limit/3);
      return "Your call is not heard.\n";
   }

   TP->add_mana(-mana_limit);
   
   if (who == TP) return "The Ancients are not pleased.\n";
   
   write("You raise your hands and summon forth the powers of shadow.\n");
   say(QCTNAME(TP) + " raises " + TP->query_possessive() + " hands and " +
       TP->query_possessive() + " eyes become as pitch.\n");
   say(QCTNAME(TP) + " intones a deep and dark sound.\n");
   who->catch_msg("You are siezed by some horrible power!\n");
   tell_room(ETP, "A shadowy rift opens and " + QTNAME(who) +
	     " is taken within.\n", who);
   seteuid(getuid());
   mvoid = clone_object(VOID);
   mvoid->set_leave_key(TP->query_real_name());
   mvoid->set_last_room(ETP);
   who->move_living("M", mvoid, 1, 1);
   return 1;
}
