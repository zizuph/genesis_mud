#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()
#define EN environment


somnus(string str){

   object am, who, sleep;

   if(TP->query_mana() < 70) return "You do not have the strength.\n";
     if(TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_FORM_CONJURATION) +
   random(100) < 160) return "You fail to summon the powers of the spirits.\n";

  am = present(MYSTIC_AMULET, TP);
   if(!am) return "You will need the amulet.\n";

     who = present(str, EN(TP));
   if(!str) who = TP;
   if(!living(who) || !who) return "Call the spirits to who?\n";

    write("Holding your amulet tightly, you invoke the chant of the spirits, calling upon their beguiling powers.\n");
  say(QCTNAME(TP) + " clutches a glowing amulet, intoning a mysterious chant.\n");
  if(who != TP){
     if(who->query_skill(SS_SPELLCRAFT) + who->query_stat(SS_DIS) +
   random(100) > 180) return "The spirits have been resisted.\n";
   }
   sleep = clone_object("/d/Terel/mecien/valley/guild/spells/sleep_obj");
   sleep->move(who);
   TP->add_mana(-70);
      return 1;
}


