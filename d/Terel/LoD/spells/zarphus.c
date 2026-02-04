/*
 * zarphus.c
 */
inherit "/d/Terel/LoD/spells/attack_spell";

#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "spells.h"

#define TP this_player()

public int
spell_fail()
{
    return (random(TP->query_skill(SS_ELEMENT_FIRE) +
                   TP->query_skill(SS_SPELLCRAFT)) <
                   random(ZARPHUS_CAST_LIMIT));
}

/* Function name: zarphus
 * Description:   calls a beam of fire upon target
 * Arguments:     str - string describing the enemy
 * Returns:       string - the error, 1 - ok
 */
nomask mixed
zarphus(string str)
{
    set_mana_cost(ZARPHUS_MANA_COST);

    switch(do_spell(str))
    {
        case 1:
            return "Who is your target?\n";
        case 2:
            return "You are a ghost, you cannot do such a thing.\n";
        case 3:
            return "Some force defends the target.\n";
        case 4:
            return "You don't dare to cast the spell.\n";
        case 5:
            return "You do not have the strength.\n";
        case 6:
            return "Your call to the evil fire is in vain.\n";
        default:
            return 1;
    }
}

public int
spell_damage(object attacker, object target)
{
    int skill;
    
    skill = ZARPHUS_ZERO_SKILL +
            attacker->query_skill(SS_SPELLCRAFT) +
            random(attacker->query_skill(SS_ELEMENT_FIRE));
    
    return F_PENMOD(ZARPHUS_PEN(attacker, target), skill);
}

public int
spell_resist(object target)
{
    return random(target->query_magic_res(MAGIC_I_RES_FIRE));
}

public void
spell_message(object attacker, object target, int phurt)
{
    string how = "misses";

    if (phurt > 0)
        how = "singes";
    if (phurt > 20)
        how = "burns";
    if (phurt > 40)
        how = "engulfs";
    if (phurt > 80)
        how = "incinerates";

    tell_watcher(QCTNAME(attacker) + " lances a beam of evil fire from " +
                 attacker->query_possessive() + " eyes at " +
                 QTNAME(target) + ".\n", attacker, target);
    attacker->catch_msg("Your beam of evil fire " + how + " " + QTNAME(target) +
                        ".\n");
    target->catch_msg(QCTNAME(attacker) + " " + how +
                      " you with a beam of evil fire emerging from " +
                      attacker->query_possessive() + " eyes.\n");
}
