/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define EN environment

init(){
   ::init();
   if(TP->query_skill(130003) > 2){
      add_action("exalt", "exalt");
   }
}

mixed
exalt(string str){
   object who, alb;
   int old;
   alb = present("holy_alb", TP);
   notify_fail("Exalt who?\n");
   if(!str) return 0;
   notify_fail("You will need the alb.\n");
   if(!alb) return 0;
   notify_fail("The alb must be worn.\n");
   if(!alb->query_worn()) return 0;
   who = present(lower_case(str), EN(TP));
   notify_fail("Who shall you exalt before the Ancients?\n");
   if(!who) return 0;
   if(!MEMBER(who)){
      TP->set_skill(PIETY, 0);
      write("Only those of the Order may be exalted, you have thus been punished.\n");
      return 1;
   }
  notify_fail("This person is not worthy of exaltations, you are made low.\n");
  if(who->query_mystic_rank() < 1) return 0;
   notify_fail("This person has passed beyond your powers.\n");
   if(who->query_mystic_rank() > 2) return 0;
   if(TP->query_mystic_rank() < 4 && who->query_mystic_rank() > 1){
      write("Such is beyond your name, you are made low by the Ancients.\n");
      TP->set_skill(PIETY, 0);
      return 1;
   }
 if(who->query_skill(EXALT) > 1 && who->query_mystic_rank() == 2){
   if(TP->query_mystic_rank() < 6){
   write("Impossible.\n");
  return 1;
   }
   who->catch_msg(QCTNAME(TP) + " grants you some special honour, touching " +
  TP->query_possessive() + " to your forehead.\n");
  TP->catch_msg("You grant " + QCTNAME(who) + " a special honour by exaltation.\n");
  tell_room(EN(TP), QCTNAME(TP) + " grants " + QCTNAME(who) + " some special honour by touching " +
   who->query_possessive() + " forehead with " + TP->query_possessive() +
  " alb.\n", ({ TP, who }));
    who->set_skill(EXALT, 3);
  return 1;
  }

   old = who->query_skill(EXALT);
   who->set_skill(EXALT, old + 1);
   TP->catch_msg("You exalt " + QCTNAME(who) + " before the Ancients, touching your alb to " + who->query_possessive() + " forehead.\n");
   who->catch_msg(QCTNAME(TP) + " touches " + TP->query_possessive() + 
      " black alb to your forehead, exalting your name before the Ancients.\n");
   tell_room(EN(TP), QCTNAME(TP) + " touches " + TP->query_possessive() + 
      " black alb to the forehead of " +QCTNAME(who) + ", exalting " +
      who->query_possessive() + " name before the Ancients.\n", ({ who, TP }));
   
   
   return 1;
   
}


void
create_armour()
{
   set_name("alb");
   set_adj("black");
   add_name("holy_alb");
   set_long("It's a full-length black vestment with close sleeves.\n"
   );
   
   add_prop("mystic_armour", 1);
   set_at(A_ARMS);
   set_ac(10);
}

public string
wear_how(int where)
{
   string how, pos;
   
   if(TP->query_skill(MYSTIC_RANK)<3){
      TP->catch_msg("You feel you have violated some order.\n");
   }
   if (this_player() == wearer)
      pos = "your";
   else
      pos = wearer->query_possessive();
   
   return " over " + pos + " head and it covers " + pos +
   " shoulders";
}


