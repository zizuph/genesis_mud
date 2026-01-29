#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "invisibility_sh";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

int location_sense_bonus;
int awareness_bonus;
int tracking_bonus;

#define ARTIRITH_DISPELLED_BY "_artirith_dispelled_by"
#define SKILL_BONUS 30
#define SKILL_CAP 100

private int determine_bonus(object spell_object, int skill, int cap) 
{
	object target = spell_object->query_effect_target();
	
	int power = spell_object->query_spell_effect_power();	
	int bonus = ftoi(log(itof(power)) * itof(SKILL_BONUS));
    int current_skill = target->query_skill(skill);
    int new_skill = MIN(current_skill + SKILL_BONUS, SKILL_CAP);
    
    return MIN(MAX(0, new_skill - current_skill), SKILL_BONUS);
}

private int increase_skill(object target, int skill, int bonus)
{
    target->set_skill_extra(skill, target->query_skill_extra(skill) + bonus);
}

void initialize_shadow(object spell_object, mapping spell_input) {
	::initialize_shadow(spell_object, spell_input);
	
	spell_object->set_spell_effect_desc("realm of shadows");
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        can_see_caster(target)->catch_msg("Employing Dark Sorcery, "
            + QTNAME(target) + " calls upon the Power of Sauron.\n"
            + capitalize(target->query_pronoun()) + " throws "
            + target->query_possessive()+ " black robe over "
            + target->query_possessive()+ " head, mumbles a few "
            + "words and fades from your view.\n");
            
        target->catch_tell("With the power the Dark Lord has bestowed upon "
            + "you, you call Artirith. You throw your robe over your head, "
            + "and mumble the dark words: 'Noro nin minna fuine, ar "
            + "tirith ketymi!'\nThe lights get blurred. You feel a strange "
            + "tranquility. The sounds seem to be muffled, yet you can hear "
            + "any of them very distinctly. Apparently you are in the realm "
            + "of shadows.\n");
			
		target->inc_prop(LIVE_I_SEE_INVIS);
        target->add_prop(LIVE_M_MOUTH_BLOCKED,"Your words sink in the "
			+ "thick air.\n");
        
        location_sense_bonus = determine_bonus(spell_object, SS_LOC_SENSE, SKILL_CAP);
        awareness_bonus = determine_bonus(spell_object, SS_AWARENESS, SKILL_CAP);
        tracking_bonus = determine_bonus(spell_object, SS_TRACKING, SKILL_CAP);
        
        increase_skill(target, SS_LOC_SENSE, location_sense_bonus);
        increase_skill(target, SS_AWARENESS, awareness_bonus);
        increase_skill(target, SS_TRACKING, tracking_bonus);
    }
    
    invis_in_effect = 1;    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    invis_in_effect = 0;

    object target = shadow_who;
    
    // Sometimes the effect did not properly end with this.
    //spell_object->query_effect_target();
    
    if (!objectp(target)) return;

    target->remove_prop(LIVE_M_MOUTH_BLOCKED);

    increase_skill(target, SS_LOC_SENSE, -location_sense_bonus);
    increase_skill(target, SS_AWARENESS, -awareness_bonus);
    increase_skill(target, SS_TRACKING, -tracking_bonus);
    target->dec_prop(LIVE_I_SEE_INVIS);

    object victim = target->query_prop(ARTIRITH_DISPELLED_BY);
    if (objectp(victim)) {
        target->catch_tell("You depart the realm of shadows in wrath!\n");
        victim->catch_msg(
              "A shadow falls suddenly over the area, growing quickly"
            + " darker as you watch. But no shadow is this, for as quickly"
            + " as you can draw a breath it has become " + QNAME(target)
            + ", who sets upon you in wrath!\n");     
        tell_room(environment(target), 
              "A shadow falls suddenly over the area, growing quickly"
            + " darker as you watch. But no shadow is this, for as quickly"
            + " as you can draw a breath it has become " + QNAME(target)
            + ", who sets upon " + QNAME(victim) + " in wrath!\n",
            ({ target, victim }));
    } else {
        target->catch_tell("You fade back into the realm of mortals.\n");
        tell_room(environment(target), 
               "A shadow stretches silently into view, growing ever darker."
            + " As you watch, it becomes clear that this is no shadow at"
            + " all, but in fact " + QNAME(target) + " who stands now"
            + " before you in plain sight.\n", target);            
    }
    target->remove_prop(ARTIRITH_DISPELLED_BY);
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel that you will soon return from "
            + "the realm of shadows.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "your presence in the realm of shadows.\n");
    }    
}

/*
 * Function:    hook_spell_no_fighting
 * Description: Override this to describe the effect when the caster 
 *              engages someone into battle.
 * Arguments:   target - our enemy that caused us to dispel the effect
 */
public void
hook_spell_no_fighting(object spell_object, object target)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->add_prop(ARTIRITH_DISPELLED_BY, target);
    }    
}
