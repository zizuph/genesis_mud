/*
 * zargmon.c
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
    return (random(TP->query_skill(SS_ELEMENT_DEATH) +
                   TP->query_skill(SS_SPELLCRAFT)) <
                   random(ZARGMON_CAST_LIMIT));
}

/* Function name: zargmon
 * Description:   calls a deadly wind upon target
 * Arguments:     str - string describing the enemy
 * Returns:       string - the error, 1 - ok
 */
nomask mixed
zargmon(string str)
{
    set_mana_cost(ZARGMON_MANA_COST);

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
            return "Your call to the deadly breath is in vain.\n";
        default:
            return 1;
    }
}

public int
spell_damage(object attacker, object target)
{
    int skill;
    
    skill = ZARGMON_ZERO_SKILL +
            attacker->query_skill(SS_SPELLCRAFT) +
            random(attacker->query_skill(SS_ELEMENT_DEATH));
    
    return F_PENMOD(ZARGMON_PEN(attacker, target), skill);
}

public int
spell_resist(object target)
{
    return random(target->query_magic_res(MAGIC_I_RES_DEATH));
}

public void
spell_message(object attacker, object target, int phurt)
{
    string verb = "misses", adverb="completely";

    if (phurt > 0) {
        verb = "chills";
        adverb = "lightly";
    }
    if (phurt > 20) {
        verb = "freezes";
        adverb = "severely";
    }
    if (phurt > 40) {
        verb = "shatters";
        adverb = "profoundly";
    }
    if (phurt > 80) {
        verb = "disrupts";
        adverb = "totally";
    }

    tell_watcher(QCTNAME(attacker) +
                 " directs an icy and deadly wind gust toward " +
                 QTNAME(target) + ". It " + verb + " " +
                 target->query_possessive() + " body " + adverb + ".\n",
                 attacker, target);
    attacker->catch_msg("Your icy and deadly wind " + verb + " " +
                        QTNAME(target) + "'s body " + adverb + ".\n");
    target->catch_msg(QCTNAME(attacker) +
                      " directs an icy and deadly wind gust toward you. It " +
                      verb + " your body " + adverb + ".\n");
}
