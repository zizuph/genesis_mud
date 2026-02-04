/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

lenire(string str){
   
   object who;
   
   if(str)
      who = present(lower_case(str), ENV(TP));
   
   if(!who)
      {
      if(!str || (str == "myself") || (str == "me")) who = TP;
      else
         return "Calm who?\n";
   }
   
  if(TP->query_mana() < 15) return "You do not have the strength.\n";

   if(TP->query_skill(SS_FORM_ABJURATION) + 
         random(TP->query_skill(SS_ELEMENT_LIFE)) < 25)
   return "You fail to hail the spirits.\n";
   
   TP->add_mana(-15);
   who->add_panic(-(random(100) + 30));
   TP->catch_msg("You hail the calming spirits of light.\n");
   tell_room(ENV(who), "A pale light hovers over " + QCTNAME(TP) + ".\n", ({ who, TP }));
   who->catch_msg("A sense of calm suddenly comforts you.\n");
   return 1;
   
}

