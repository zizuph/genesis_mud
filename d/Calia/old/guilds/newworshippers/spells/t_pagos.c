/*
    Ice weapon spell for the Elemental worshippers.

    Coded July 2004, Bishop of Calia.
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell.c";
 
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

object comp;

public object *
special_target_one_present_object(object caster, string str)
{
    mixed *oblist;

    object *gems = filter(deep_inventory(caster), &operator(==)("quartz") @ 
        &->query_gem_name());
    
    if (!sizeof(gems))
    {
        caster->catch_tell("You need a rose quartz in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }

    comp = gems[0];

    if (!strlen(str) || !parse_command(str, all_inventory(caster) +
        all_inventory(environment(caster)), "[at] / [on] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	caster->catch_tell("What do you wish to target?\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
	caster->catch_tell("You will have to be more specific!  You can only " +
	  "select one target.\n");
	return ({});
    }
    
    if (!present(oblist[0], caster))
    {
        caster->catch_tell("You can only enchant something that is in your" +
            " possession!\n");
        return ({});
    }
    
    if (oblist[0]->query_wielded() != caster)
    {
        caster->catch_tell("You can only enchant a weapon that you are" +
            " wielding!\n");
        return ({});
    }
    
    if (oblist[0]->query_prop(OBJ_I_HAS_FIRE))
    {
        caster->catch_tell("That weapon is too hot to enchant with ice!\n");
        return ({});
    }
    
    if (oblist[0]->query_magic_res(MAGIC_I_RES_COLD) >= 30 ||
        oblist[0]->query_magic_res(MAGIC_I_RES_MAGIC) >= 30 ||
        oblist[0]->query_magic_res(MAGIC_I_RES_WATER) >= 30 ||
        oblist[0]->query_prop(OBJ_M_NO_MAGIC))
    {
        caster->catch_tell("The weapon resists your attempt to enchant it.\n");
        return ({});
    }
    
    if (oblist[0]->query_pen() >= 55 || oblist[0]->query_hit() >= 55)
    {
        caster->catch_tell("That weapon is too powerful for you to" +
            " enchant.\n");
        return ({});
    }
    
    if (oblist[0]->query_likely_break() >= 20)
    {
        caster->catch_tell("That weapon is too brittle to enchant. You are" +
            " afraid you might end up destroying it.\n");
        return ({});
    }
    if (oblist[0]->has_pagos_shadow())
    {
        caster->catch_tell("That weapon is already under the effect of the" +
            " Pagos enchantment!\n");
        return ({});
    }
    

    return oblist;
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
    set_spell_name("pagos");
    set_spell_desc("Enchant a weapon with the cold of Lord Diabrecho");
    set_spell_target(special_target_one_present_object);
    set_spell_time(5);
    set_spell_mana(50);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_peaceful(1);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object("/d/Calia/newworshippers/spells/pagos_obj");
    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to murmur the Pagos incantation.\n");
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
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
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    caster->catch_tell("As you complete the Pagos incantation, you run your" +
        " hand along the length of your " + targets[0]->short() + ". The" +
        " passage of your hand leaves a film of ice on it, radiating" +
        " intense cold.\n");
    say("As " + QTNAME(caster) + " completes " + 
        caster->query_possessive() + " incantation, " + caster->query_pronoun()
        + " runs " + caster->query_possessive() + " hand along the length" + 
        " of " + caster->query_possessive() + " " + targets[0]->short() + "." +
        " The passage of " + caster->query_possessive() + " hand leaves a" +
        " film of ice on the weapon.\n", caster); 
        
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result);
    
    //One in three that component is sacrificed.
    if (!random(3))
    {
        caster->catch_tell("You sacrificed a rose quartz.\n");
        comp->set_heap_size(comp->num_heap() - 1);
    }
                    
}