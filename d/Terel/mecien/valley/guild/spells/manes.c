/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"
#define TO this_object()
#define TP this_player()
#define ENV environment
#define QS query_skill

manes(){
   
   object ghost;
   
   if(TP->query_mana() < 75) return "You do not have the strength.\n";
   if(TP->QS(SS_ELEMENT_DEATH) < 50) return "Learn the ways of darkness and death.\n";
   if(random(TP->QS(SS_ELEMENT_DEATH)) + random(TP->QS(SS_FORM_ENCHANTMENT)) +
         random(TP->QS(SS_SPELLCRAFT)) < 100) return "You fail to summon the abyss to your side.\n";
   
   TP->catch_msg("You speak the words of death and darkness.\n");
   tell_room(ENV(TP), QCTNAME(TP) + " places " + TP->query_possessive() + 
      " hands over " + TP->query_possessive() + 
      " heart and speaks unfathomable words.\n", TP);
   set_alarm(2.0, -1.0, "darkness");
   set_alarm(4.0, -1.0, "simul_death");
   TP->add_mana(-75);
   return 1;
}

darkness(){
   TP->catch_msg("The powers of the abyss shroud around you!\n");
   tell_room(ENV(TP), "Horrifying darkness seems to shroud around " +
      QCTNAME(TP) + ", who cries out in agony as it envelops " + TP->query_objective() + "!\n", TP);
}

simul_death(){
   object ghost;
   TP->catch_msg("You seem to die, but take on another spiritual life.\n");
   tell_room(ENV(TP), QCTNAME(TP) + " dies.\n", TP);
   tell_room(ENV(TP), "The corpse of " + QTNAME(TP) + 
  " dissolves into the darkness around it.\n", TP);
   ghost = clone_object(PATH + "spells/ghost");
   ghost->move(TP);
   ghost->set_duration(TP->QS(SS_ELEMENT_DEATH) / 3);
}


