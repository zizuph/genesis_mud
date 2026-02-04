/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
* flammis.c
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
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()


public int
query_components()
{
   object lamp = present(MYSTIC_LAMP, TP), ember;
   
   if (!lamp) return 0;
   
   ember = present(MYSTIC_EMBER, lamp);
   
   if (!ember) return 0;
   
   if (random(100) > 95) {
       if (lamp->remove_ember())
           TP->catch_msg("Your lamp flickers and grows cold.\n");
   }
   
   return 1;
}

int
spell_fail()
{
   return (random(TP->query_skill(SS_ELEMENT_FIRE) +
         TP->query_skill(SS_FORM_CONJURATION)) < random(FLAMMIS_CAST_LIMIT));
}

/* Function name: flammis
 * Description:   calls an arc of fire upon target
 * Arguments:     str - string describing the enemy
 * Returns:       string - the error, 1 - ok
 */
nomask mixed
flammis(string str)
{
   
   set_mana_cost(FLAMMIS_MANA_COST);
   
   switch(do_spell(str))
   {
      case 1:
      return "What is thy target?\n";
      break;
      case 2:
      return "You are a ghost, you cannot do such a thing.\n";
      case 3:
      return "Some force defends the target.\n";
      case 4:
      return "You don't dare to cast the spell.\n";
      case 5:
      return "You do not have the strength.\n";
      case 6:
      return "Your call to the mystic fire is in vain.\n";
      case 7:
      return "The sacred fire is not with you.\n";
      default:
      return 1;
   }
}

int
spell_damage(object attacker, object target)
{
   return F_PENMOD(90,
      attacker->query_skill(SS_FORM_CONJURATION) +
      random(attacker->query_skill(SS_ELEMENT_FIRE)) + 50 + SS_OCCUP);
}

int
spell_resist(object target)
{
   return target->query_magic_res(MAGIC_I_RES_FIRE);
}

void
spell_message(object attacker, object target, int phit)
{
   string how;
   
   how = "misses";
   if (phit > 0)
      how = "singes";
   if (phit > 20)
      how = "burns";
   if (phit > 50)
      how = "engulfs";
   if (phit > 100)
      how = "incinerates";
   
   tell_watcher(QCTNAME(attacker) + " lances an arc of fire at "
      + QTNAME(target) + ".\n", attacker, target); 
   attacker->catch_msg("Your arc of fire " + how + " " + QTNAME(target) + ".\n");
   target->catch_msg(QCTNAME(attacker) + " " + how + " you with an arc of fire.\n");
}
