/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This is the mystic 'avis' spell */
#include <stdproperties.h>
#include <macros.h>
#include <comb_mag.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define SPELL_COST 5
#define ALIGN_LIM  -300
#define TP         this_player()
#define ENV        environment
#define STD_RET    "Avis who?\n"

public void omen(object who, object rec);

nomask mixed
avis(string str)
{
   object rec;

   if (NPMAGIC(TP)) return "Somehow your spell fails.\n";

   if (TP->query_mana() < SPELL_COST)
       return "You do not have the strength.\n";

   if (!str) return STD_RET;
   
   rec = find_living(lower_case(str));
   if (!rec || NPMAGIC(rec) || rec->query_wiz_level())
       return STD_RET;

   TP->catch_msg("You summon forth the spirits of darkness " +
                 "to send forth their gloom.\n");
   say(QCTNAME(TP) + " dispatches a shadowy spirit that arises " +
       " from the ground.\n");
   
   set_alarm(10.0, -1.0, &omen(TP, rec));

   TP->add_mana(-SPELL_COST);
   return 1;
}

public void
omen(object who, object rec)
{
   if (!rec || NPMAGIC(rec)) return;
   
   if (who) {
      who->catch_msg("The shadowy spirit now descends on " + QTNAME(rec) +
                     ".\n");
   }

   if (rec->query_alignment() < ALIGN_LIM) {
      tell_room(ENV(rec), "A dark mysterious shape hovers over " +
                QTNAME(rec) + ".\n", rec);
      rec->catch_msg("A dark mysterious shape hovers over you. " +
                     "You feel a deep pain in your chest.\n");
      return;
   }
   
   switch (random(4)) {
      case 0:
        rec->catch_msg("A bright white light shines down upon you.\n");
        break;
      case 1:
        rec->catch_msg("A pain strikes your right arm.\n");
        rec->command("$cough");
        break;
      case 2:
        rec->catch_msg("You sense some great danger.\n");
        break;
      case 3:
        rec->catch_msg("You sense that you have displeased some " +
                       "great power and it is best to atone.\n");
        break;
   }
}
