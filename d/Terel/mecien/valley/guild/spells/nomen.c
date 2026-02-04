/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <macros.h>
#include <std.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define MANA_LIMIT    30
#define CAST_LIMIT    50  /* The limit for this to become a success */
#define NOMEN         (GUILD_DIR + "archive/archive.tome")
#define TP            this_player()
#define ETP           environment(TP)
#define ETPINV        all_inventory(ETP)

/* Function name: nomen
 * Description:   mystic divines name of object/player
 * Arguments:     str - target
 * Returns:       1/0
 */
nomask mixed
nomen(string target)
{
   object who=0, *obs;
   int n, found, mana_limit, suc;
   string *names, nam, tit, myentry;

   if (!target) return "Whom shall be remembered?\n";

   if (target == "me" || target == "myself")
       who = TP;
   else {
       if (!parse_command(lower_case(target), ETPINV, "%l", obs))
           return "Whom shall be remembered?\n";
       if (sizeof(obs) <= 1)
           return "Whom shall be remembered?\n";
       else {
           who = obs[1];
           if (!CAN_SEE(TP, who)) return "Whom shall be remembered?\n";
       }
   }

   if (NPMAGIC(who))
       return "Something or somebody has blocked your power.\n";

   if (who == TP) {
       seteuid(getuid());
       found = 0;
       names = ({});
       myentry = TP->query_name() + " " + TP->query_title();
       if (file_size(NOMEN) > 0)
           names = explode(read_file(NOMEN), "\n");
/* Replace old entry if it exists */
       for (n=0; n<sizeof(names); n++) {
           sscanf(names[n], "%s %s", nam, tit);
           if (nam == TP->query_name()) {
               names[n] = myentry;
               found = 1;
               break;
           }
       }
       if (!found) names += ({myentry});

       if (file_size(NOMEN) >= 0) rm(NOMEN);
       for (n=0; n<sizeof(names); n++) write_file(NOMEN, names[n]+"\n");
       write("Thy name shall be known to all ages.\n");
       return 1;
   }

   mana_limit = MANA_LIMIT;

   if (TP->query_mana() < mana_limit)
      return "You are too weak to attempt this.\n";

   suc  = TP->query_skill(SS_FORM_DIVINATION);
   suc += TP->query_skill(SS_SPELLCRAFT);
   suc -= who->query_skill(SS_FORM_ABJURATION);
   if (random(suc) < random(CAST_LIMIT))
   {
      TP->add_mana(-mana_limit / 3);
      return "You divine nothing.\n";
   }

   if (SECURITY->query_wiz_rank(who->query_real_name()))
       return "A divine power shall never be touched.\n";

   TP->add_mana(-mana_limit);
   write("You seek the wisdom of Antiquity.\n");
   say(QCTNAME(TP) + " raises a hand and speaks some mystic words.\n");
   who->catch_msg("A strange power touches you.\n");
   write("A mysterious voice intones: " + who->query_name() +
         ", is the name within.\n");
   TP->add_introduced(who->query_real_name());
   return 1;
}
