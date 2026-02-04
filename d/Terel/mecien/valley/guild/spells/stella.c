/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * stella.c
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

#define TP this_player()
int
spell_fail()
{
    return (random(this_player()->query_skill(SS_ELEMENT_FIRE) +
        this_player()->query_skill(SS_FORM_CONJURATION)) < random(STELLA_CAST_LIMIT));
}

/* Function name: stella
 * Description:   a shard of starlight is bolted against enemy
 * Arguments:     str - string describing the enemy
 * Returns:       string - the error, 1 - ok
 */
nomask mixed
stella(string str)
{
    set_mana_cost(STELLA_MANA_COST);

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
            write("Your call to the holy stars is in vain.\n");
            return 1;
        default:
            return 1;
    }
}

int
spell_damage(object attacker, object target)
{
  if(present("star_pendant", TP)){
  return F_PENMOD(STELLA_PEN, (attacker->query_skill(SS_ELEMENT_FIRE) +
   attacker->query_stat(SS_WIS)) /5 + 25);
}
    return F_PENMOD(STELLA_PEN, (attacker->query_skill(SS_ELEMENT_FIRE) +
        attacker->query_stat(SS_WIS)) / 5  + 15);
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
        how = "stuns";
    if (phit > 10)
        how = "strikes";
    if (phit > 25)
        how = "illuminates";
    if (phit > 40)
        how = "hammers";
  
  if(!present("star_pendant", attacker)){
    tell_watcher(QCTNAME(attacker) + " raises a hand and a bolt of light "
       + how + " " + QTNAME(target) + ".\n", attacker, target); 
    attacker->catch_msg("You call a bolt of starlight that " + how + " " +
       QTNAME(target) + ".\n");
    target->catch_msg(QCTNAME(attacker) + " " + how + " you with a bolt of light.\n");
}
if(present("star_pendant", attacker)){
    tell_watcher(QCTNAME(attacker) + " raises a silver pendant and a bolt of light "
       + how + " " + QTNAME(target) + ".\n", attacker, target); 
   attacker->catch_msg("You grip your silver pendant and it grows fiery!\n");
    attacker->catch_msg("You call a bolt of starlight that " + how + " " +
       QTNAME(target) + ".\n");
    target->catch_msg(QCTNAME(attacker) + " " + how + " you with a bolt of light.\n");
}
}
