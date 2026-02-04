#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define EN environment
#define TP this_player()
#define TO this_object()

venustas(string str){

  object who, charm;


  if(TP->query_mana() < 50) return "YOu do not have the strength.\n";
   if(TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_FORM_ENCHANTMENT) +
  random(100) < 120) return "Your incantation did not take shape.\n";

   if(!str) return "Your incantation is void.\n";
  who = present(str, EN(TP));
   if(!who || !living(who) || who == TP) return "Your incantation fails to gather upon someone.\n";

     write("You incant the charms of the ancient world, calling upon the spirits of magic to weave their powers.\n");
   say(QCTNAME(TP) + " starts incanting a mesmerising chant, a strange glow " +
  "appearing upon " + TP->query_possessive() + " face.\n");

    who->catch_msg("A warm feeling passes over you.\n");
  who->command("smile lov");

  TP->add_mana(-50);
     charm = clone_object("/d/Terel/mecien/valley/guild/spells/charm");
  charm->move(who);
   return 1;
}


