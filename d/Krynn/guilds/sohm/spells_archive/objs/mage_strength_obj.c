/*
 * Magic Strength object for SOHM 
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/unfinished/regen_mana_obj";

#include "/d/Genesis/specials/calculations.c"

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

public mapping      stat_boost_mapping = ([ ]);

// For the purposes of testing, the duration time increased by 5
#define TEST_MOD    5.0

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_sohm_mage_strength_object_");
    set_short("mage strength mana regen object");    
    set_long("This is a mage strength spell object. It regenerates "
        + "the caster's mana.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the SoHM mage strength spell.\n");
    set_spell_effect_desc("mage strength");

    set_element_skill_effect(SS_ELEMENT_EARTH);  

    // Duration determined as a factor of spell power
    int power = query_spell_effect_power();
    int duration = ftoi(itof(power) * 30.0 * TEST_MOD);
    set_dispel_time(duration);
  
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();

    if (!result)
    {
        return result;
    }
    int power = query_spell_effect_power();    
    object player = query_effect_target();

    stat_boost_mapping[SS_STR] = convert_caid_to_stat(player, 9, SS_STR);
    player->set_stat_extra(SS_STR, player->query_stat_extra(SS_STR)
    + stat_boost_mapping[SS_STR]);
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    object player = query_effect_target();
    foreach (int stat_id, int boost : stat_boost_mapping)
    {
        player->set_stat_extra(stat_id, player->query_stat_extra(stat_id)
        - stat_boost_mapping[stat_id]);
    }   
    return 1;
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel your mind and body being transformed with "
        + "magical energies and grow noticably stronger.\n");
        tell_room(environment(target), QCTNAME(target) + " looks mentally and "
        + "physically stronger as " + target->query_possessive() + " body is "
        + "transformed with magical energies.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel yourself weakening as your mage strength "
        + "spell wears off.\n");
    }    
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your mage strength spell is " +
            "beginning to wane.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "your mage strength spell.\n");
    }    
}

/*
 * Function:    hook_describe_regeneration
 * Description: Mask this to give messages for when the target gets healed
 *              by the regeneration effect.
 */
public void
hook_describe_regeneration(object target, int amount)
{       
    target->catch_tell("You feel the infused minotaur blood you consumed " +
                    "invigorate your mind!\n");
}

/*
 * Function:    query_mana_regen_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */

public string
query_mana_regen_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are infused with transformative energies, enhancing " +
                "your mind and body.\n";
    else
        return capitalize(on->query_pronoun()) + " is enhanced with " +
           "transformative energies.\n";
}
