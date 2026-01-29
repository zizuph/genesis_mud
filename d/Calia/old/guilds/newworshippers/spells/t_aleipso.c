/*
  This is the Aleipso (heal) spell for the Worshippers.

  Coded by Bishop of Calia, June 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/heal.c";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"


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
    set_spell_name("aleipso");
    set_spell_desc("Heal someone using the gifts of Lord Diabrecho");
    set_spell_target(spell_target_one_present_living);

    set_spell_time(4);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 35);
    set_spell_ingredients(({"cladina"}));
    set_spell_resist(spell_resist_healing);

    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    if (caster == targets[0])
    {
        caster->catch_tell("You begin to murmur the Aleipso incantation," +
            " focusing on your own wounds.\n");
    }
    else
    { 
        caster->catch_msg("You begin to murmur the Aleipso incantation," +
            " focusing on " + LANG_POSS(QTNAME(targets[0])) + " wounds.\n");
    }
    
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
}

/*
 * Function name: desc_heal
 * Description:   Describe the spell casting and effect.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object *targets - the targets
 *                int *heal - Healing in hps for each target
 */
public void
desc_heal(object caster, object *targets, int *heal)
{
    string desc1, desc2;
    
    if (heal[0] < 280)
    {
        desc1 = "a few";
        desc2 = "a mild chill runs down your spine.\n";
    }
    else
    if (heal[0] < 360)
    {
        desc1 = "some";
        desc2 = "you experience strong chills.\n";
    }
    else
    {
        desc1 = "many";
        desc2 = "you feel as if you've been dipped in icy water.\n";
    }
    
    
    if (caster->query_wiz_level())
    {
        caster->catch_tell("Heal amount is: " + heal[0] + ".\n");
    }
    
    if (targets[0] == caster)
    {       
        caster->catch_msg("Harnessing the power granted to you by Lord" +
            " Diabrecho, you move your hands over your own wounds.\n" +
            "The healing power of your patron courses through you, and " +
            desc2);
        say(QCTNAME(caster) + " moves " + caster->query_possessive() +
            " hands over " + caster->query_possessive() + " wounds," +
            " causing " + desc1 + " of them to close.\n");
    }
    else
    {
        caster->catch_msg("Harnessing the power granted to you by Lord" +
            " Diabrecho, you move your hands over " + 
            LANG_POSS(QTNAME(targets[0])) + " wounds.\n" +
            "Energy flows from your hands into " + 
            targets[0]->query_objective() + " and " + desc1 + " of " +
            targets[0]->query_possessive() + " wounds close.\n"); 
        targets[0]->catch_msg(QCTNAME(caster) + " moves " +
            caster->query_possessive() + " hands over your wounds.\n" +
            "Energy flows into you and " + desc2);
        say(QCTNAME(caster) + " moves " + caster->query_possessive() +
            " hands over " + LANG_POSS(QTNAME(targets[0])) + " wounds," +
            " causing " + desc1 + " of them to close. " +
            QCTNAME(targets[0]) + " shivers slightly.\n",
            ({targets[0], caster}));
    }
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
    int *heal = allocate(sizeof(targets));
    
    if (resist[0] > random(100))
    {
        caster->catch_tell("You complete the spell, but your target" +
            " is unaffected.\n");
        return;
    }

    heal[0] = (100 - resist[0]) * min(200 + 
        random(caster->query_stat(SS_LAYMAN)) + 
        random(caster->query_stat(SS_LAYMAN)), 400) / 100;
        
    if (targets[0]->query_hp() != targets[0]->query_max_hp())
    {
        targets[0]->heal_hp(heal[0]);
        desc_heal(caster, targets, heal);
    }
    else
    {
        caster->catch_tell("Your target is not hurt, so your spell" +
            " has no effect.\n");
        //Regain half the mana if it turns out target is unhurt.
        caster->add_mana(60);
    }
}
