
/*
 * bdella.c
 *
 * Bdella (Soul Leech) spell for the Spirit Circle of Psuchae
 * This will give the target a stat poison
 *
 * Copyright (C): Jaacar, August 4th, 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <poison_types.h>

#include "defs.h"
#include SPIRIT_HEADER

#define I_WAS_SPIRIT_SOUL_LEECHED "_i_was_spirit_soul_leeched"
#define POISON_OBJECT "/std/poison_effect"

string
query_spell_level()
{
    return "Master";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("bdella");
    set_spell_desc("Soul Leech");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(3);
    set_spell_mana(150);
    set_spell_vocal(0);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_SPIRIT, 75);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
    set_spell_ingredients(({"diamond"}));
    set_spell_stationary(1);
    set_spell_offensive(1);
    add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
    if (caster->query_intoxicated())
    {
        caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
            "good aligned.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You summon the energies of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object poison;
    int gstat, spirit, enchantment, time;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but the spell didn't "+
            "work for some reason.");
        return;
    }
    if (targets[0]->query_prop(I_WAS_SPIRIT_SOUL_LEECHED))
    {
        caster->catch_msg("You can only use this gift on any target once.\n");
        return;
    }
    gstat = caster->query_stat(SS_OCCUP);
    spirit = caster->query_skill(SS_ELEMENT_SPIRIT);
    enchantment = caster->query_skill(SS_FORM_ENCHANTMENT);

    /* The poison will go off a maximum of 12 times, lowering stats
       12 points maximum */

    time = MAX(300,(gstat + spirit + enchantment));

    caster->catch_tell("You channel the energies of Psuchae and point at "+
        targets[0]->query_the_name(caster)+". "+
        capitalize(targets[0]->query_pronoun())+" appears to begin to "+
        "weaken.\n");
    say(QCTNAME(caster)+" points at "+QNAME(targets[0])+".\n",({caster}));
    targets[0]->add_prop(I_WAS_SPIRIT_SOUL_LEECHED,1);
    setuid();
    seteuid(getuid());
    poison = clone_object(POISON_OBJECT);
    poison->move(targets[0]);
    poison->set_time(time);
    poison->set_interval(10);
    poison->set_strength(40);
    poison->set_damage(({POISON_STAT, SS_STR, POISON_STAT, 
        SS_DEX, POISON_STAT, SS_CON, POISON_HP, 30}));
    poison->start_poison(caster);
    
}
