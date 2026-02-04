/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
* fulmen.c
*/
inherit "/d/Terel/mecien/valley/guild/spells/attack_spell";
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "spells.h"

int
spell_fail()
{
   return (random(this_player()->query_skill(SS_ELEMENT_AIR) +
         this_player()->query_skill(SS_FORM_CONJURATION)) < random(FULMEN_CAST_LIMIT));
}

/* Function name: fulmen
* Description:   calls a bolt of lightning upon target
* Arguments:     str - string describing the enemy
* Returns:       string - the error, 1 - ok
*/
nomask mixed
fulmen(string str)
{
   set_mana_cost(FULMEN_MANA_COST);
   
   if(!present("mystic_cloud", environment(this_player())))
      return "No storm is present.\n";
   
   switch(do_spell(str))
   {
      case 1:
      return "What is thy target?\n";
      case 2:
      return "You are a ghost, you cannot do such a thing.\n";
      case 3:
      return "Some force defends the target.\n";
      case 4:
      return "You don't dare to cast the spell.\n";
      case 5:
      return "You do not have the strength.\n";
      case 6:
      write("Your call to the ancient light is not heard.\n");
      return 1;
      default:
      return 1;
   }
}

/*
* This is called from within the combat system
*/
int
spell_damage(object attacker, object target)
{
   return F_PENMOD(FULMEN_PEN, (attacker->query_skill(SS_FORM_CONJURATION) + 
         attacker->query_skill(SS_ELEMENT_AIR)) / 2 + (random(70)) + 40);
}

int
spell_resist(object target)
{
   return target->query_magic_res(MAGIC_I_RES_ELECTRICITY);
}


void spell_message(object attacker, object target, int phit)
{
   string how;
   
   if (phit > 200)
      how = "cataclysmic";
   else if (phit > 120)
      how = "devastating";
   else if (phit > 60)
      how = "scorching";
   else if (phit > 30)
      how = "gripping";
   else if (phit > 0)
      how = "searing";
   else
      how = "powerless";
   
   tell_watcher(QCTNAME(attacker) + " calls out to the heavens and "
      + QTNAME(target) + " is struck with a " + how + " bolt of lightning from the storm.\n",
      attacker, target); 
   attacker->catch_msg("You call a " + how + " bolt of lightning from the storm down upon "
      + QTNAME(target) + ".\n");
   attacker->catch_msg(QCTNAME(target) + " calls down a " + how +
      " bolt of lightning from the storm upon you.\n");
}
