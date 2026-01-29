/*
 * Cheiropoto
 *
 * At will damage spell for the Academics of Elemental Arts. This is based
 * on the Genesis generic At-Will Harm spell.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/at_will_harm";

// Defines
#define CHEIROPOTO_ELEMENT          "_cheiropoto_element"
#define CHEIROPOTO_SUBELEMENT       "_cheiropoto_subelement"

#include "/d/Calia/guilds/academics/spells/cheiropoto_desc.h"

/*
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_at_will_spell()
{
    set_spell_name("cheiropoto");
    set_spell_desc("Call upon the elements to strike your enemy");
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_ABJURATION, 10);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(15.0);
    set_spell_task(TASK_EASY);    
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
public int
query_spell_element_skill()
{
    // This should end up returning whatever specialization the player
    // has for the skill.
    object player = this_player();

    // Spell's element is determined during concentrate_msg and stored.
    int element_skill = player->query_prop(CHEIROPOTO_ELEMENT);
    
    send_debug_message("cheiropoto", capitalize(player->query_real_name())
        + " casting cheiropoto with element " + element_skill + ".");
        
    return element_skill;
}

public int
is_cheiropoto_activated(object caster)
{
    if (ignore_spell_ingredients(caster))
    {
        // People who don't need ingredients also don't need to have it
        // activated.
        return 1;
    }
    
    // When the caster becomes elementally focused, we set a
    // expire time. Here, we check whether we are still within
    // that expire time.
    if (present("_academic_focus_object_", caster))
    {
        return 1;
    }

    return 0;        
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a member of the Academy!\n");
        return 0;
    }
    
    if (ACADEMIC_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules. Please see <help academic "
            + "rules>.\n");
        return 0;
    }
    
    // Cheiropoto is an at will spell that needs to be activated and
    // then last for some time.
    if (!is_cheiropoto_activated(caster))
    {
        caster->catch_tell("In order to cast cheiropoto, you have "
            + "to be elementally focused.\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return ACADEMIC_MANAGER->acquired_elemental_spell(player);
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    int * elements = ({ SS_ELEMENT_FIRE, SS_ELEMENT_WATER, 
                        SS_ELEMENT_AIR, SS_ELEMENT_EARTH });
    int primary_element = ACADEMIC_MANAGER->query_primary_element_skillnum(caster);
    elements -= ({ primary_element });

    // 70% chance of going with their primary element. 10% chance
    // each for the other elements.
    int chosen_element;
    if (!primary_element)
    {
        chosen_element = elements[random(sizeof(elements))];
    }
    else
    {
        switch (random(100))
        {
        case 0..39:
            chosen_element = primary_element;
            break;
        
        case 40..59:
            chosen_element = elements[0];
            break;
                
        case 60..79:
            chosen_element = elements[1];
            break;
                    
        case 80..99:
        default:
            chosen_element = elements[2];
            break;           
        }
    }
    // We set the property here so the other functions can know
    // which element they're currently in the process of casting.
    caster->add_prop(CHEIROPOTO_ELEMENT, chosen_element);

    switch (chosen_element)
    {
    case SS_ELEMENT_FIRE:
        fire_concentrate_msg(caster);
        break;
        
    case SS_ELEMENT_WATER:
        water_concentrate_msg(caster);
        break;
    
    case SS_ELEMENT_AIR:
        air_concentrate_msg(caster);
        break;
    
    case SS_ELEMENT_EARTH:
    default:
        earth_concentrate_msg(caster);
        break;
    }
    
    setuid();
    seteuid(getuid());
    ACADEMIC_MANAGER->add_practice_level(caster, 1);    
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete()
{
    write("You sense the power of the elements stirring within you and "
        + "feel ready again to invoke the powers of cheiropoto.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready yet to call upon the powers of "
        + "cheiropoto.\n");
}

public void
hook_already_active(object ability)
{
    write("You are already summoning upon the power of the elements "
        + "to attack your foe!\n");
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    object target = targets[0];
    int element = caster->query_prop(CHEIROPOTO_ELEMENT);
    switch (element)
    {
    case SS_ELEMENT_FIRE:
        fire_desc_cast(caster, target);
        break;
    
    case SS_ELEMENT_WATER:
        water_desc_cast(caster, target);
        break;
    
    case SS_ELEMENT_AIR:
        air_desc_cast(caster, target);
        break;
    
    case SS_ELEMENT_EARTH:
    default:
        earth_desc_cast(caster, target);
        break;
    }
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    int element = caster->query_prop(CHEIROPOTO_ELEMENT);
    switch (element)
    {
    case SS_ELEMENT_FIRE:
        fire_desc_damage(caster, target, result);
        break;
    
    case SS_ELEMENT_WATER:
        water_desc_damage(caster, target, result);
        break;
    
    case SS_ELEMENT_AIR:
        air_desc_damage(caster, target, result);
        break;
    
    case SS_ELEMENT_EARTH:
    default:
        earth_desc_damage(caster, target, result);
        break;
    }
}

/*
 * Function:    query_insufficient_skills
 * Description: Returns the skills that are not high enough to cast this
 *              spell.
 */
public int *
query_insufficient_skills(object caster)
{
    int * needed_skills = ({ });
    int * check_skills = ({ SS_ELEMENT_FIRE, SS_ELEMENT_WATER, SS_ELEMENT_AIR,
        SS_ELEMENT_EARTH, SS_FORM_ABJURATION });
    
    foreach (int snum : check_skills)
    {
        // minimum of superior student
        if (caster->query_skill(snum) < 10)
        {
            needed_skills += ({ snum });
        }
    }

    return needed_skills;
}
