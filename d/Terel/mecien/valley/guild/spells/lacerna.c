/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>
#include "/d/Terel/mecien/valley/guild/spells/spells.h"

#define TP this_player()
#define COST 50
#define LIMIT 60
#define ENV environment

nomask mixed
lacerna(string str){
   
    object who, obj, ob;
   
   if(str)
      who = present(lower_case(str), environment(TP));
   if(!who)
      {
      if(!str || (str == "me"))
         who = TP;
      else
         return "Upon whom shall you lay the mantle?\n";
   }
   if(NPMAGIC(who))
      return "Something blocks your powers.\n";
   
   if(TP->query_mana() < COST)
      return "You are too weak to attempt this.\n";
   
   if(random(TP->query_skill(SS_FORM_DIVINATION)) +
         random(TP->query_skill(SS_ELEMENT_LIFE)) < LIMIT)
   return "Your call to the mystery in unheard.\n";
   
   obj = present("sacred_mantle", TP);
   if(!obj)
   return "You do not possess the sacred mantle.\n";

   TP->catch_msg("You invoke the spiritual mantle of the ancients.\n");
   tell_room(ENV(TP), QCTNAME(TP) + " clutches " +
      TP->query_possessive() + " mantle and whispers a short prayer.\n",
      TP);
   TP->add_mana(-COST);
   
   seteuid(getuid(this_object()));
   ob = clone_object("/d/Terel/mecien/valley/guild/spells/sp_mant");
    ob->set_duration(DURATION(TP->query_stat(SS_OCCUP),
    TP->query_skill(SS_SPELLCRAFT), 100));
  ob->move(who);
   return 1;
}

