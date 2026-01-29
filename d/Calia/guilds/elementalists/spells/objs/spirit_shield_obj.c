/*
 * Spirit Shield for the Aitheras Spell for the Elementalists of Calia
 *
 * Created by Petros, January 2013
 */
 
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/regen_mana_obj";

// Defines
#define NOTIFICATION_INTERVAL   30.0
#define SPIRITSHIELD_SUBLOC "_spiritshield_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_schirmo_spirit_object_");
    set_short("schirmo spirit shield object");    
    set_long("This is the schirmo spirit shield object. It regenerates "
        + "the caster's mana.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the schirmo elemental shield spell.\n");
}


public int
setup_spell_effect()
{
    set_spell_effect_desc("schirmo spirit shield");    
    return ::setup_spell_effect();
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

    if (!objectp(target))
    {
        return;
    }
    object caster = query_effect_caster();
    
    string caster_message = "As you complete your prayer to Psuchae, "
        + "you sense the spirit in the shadows stir as it grants its "
        + "revitalizing spirit for your use. ";
    string target_message = "Filaments of shadow appear out of nowhere and "
        + "coalesce around you until the shadow surrounds your entire body, "
        + "forming a thin regenerative layer of shadow upon your skin.\n";
    string watcher_message = "Filaments of shadow appear out of nowhere and "
        + "coalesce around " + QTNAME(target) + " until the shadow surrounds "
        + target->query_possessive() + " entire body, forming a thin "
        + "layer of shadow upon " + target->query_possessive() + " skin.\n";
    if (target == query_effect_caster())
    {
        caster->catch_msg(caster_message + target_message);
    }
    else
    {
        caster->catch_msg(caster_message + "\n");
        target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
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
    if (!objectp(target))
    {
        return;
    }
    
    target->catch_tell("The energy sustaining layer of shadow upon your skin "
        + "dissipates, leaving you feeling a bit hollow.\n");
    tell_room(environment(target), "The translucent layer of shadow upon "
        + QCTPNAME(target) + " skin dissipates, leaving " 
        + target->query_objective() + " a feeling a bit hollow.\n",
        ({ target }));
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
    if (!objectp(target))
    {
        return;
    }
    
    target->catch_tell("You sense the cohesion in the layer of shadow upon "
        + "your skin begin to weaken.\n");
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
            + "the Schirmo gift of Psuchae.\n");
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
    switch (random(2))
    {
    case 1:
        target->catch_tell("The energy sustaining layer of shadow thickens "
            + "around you, speeding up your mental recovery.\n");
        break;
    
    default:
        target->catch_tell("You feel the translucent "
            + "layer of shadow moving throughout your body, recovering "
            + "your mental energies.\n");
        break;
    }       
}

/*
 * Function:    query_spiritshield_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_spiritshield_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "A translucent energy sustaining layer of shadow closely "
            + "wraps your body.\n";
    else
        return capitalize(on->query_pronoun()) + " has a translucent "
            + "layer of shadow upon " + on->query_objective()
            + " skin.\n";
}

// Subloc Information

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person has a beating heart now
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (interactive(to))
    {
        to->add_subloc(SPIRITSHIELD_SUBLOC, this_object());        
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (interactive(old))
    {
        old->remove_subloc(SPIRITSHIELD_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != SPIRITSHIELD_SUBLOC)
    {
        return "";
    }
    
    return query_spiritshield_subloc_description(on, for_obj);
}

/*
 * Function:    do_regeneration
 * Description: The function that gets called every interval to heal
 *              the target.
 */
 
 /*
public void
do_regeneration()
{
    object target = query_effect_target();
    if (!objectp(target) || target->query_linkdead() 
        || target->query_linkdead_in_combat())
    {
        return;
    }

    int maxmana = target->query_max_mana();
    int currentmana = target->query_mana();
    if (maxmana == currentmana)
    {
        // No need for regeneration
        return;
    }
    
    int mana_amount = (calculate_heal_amount(target));
    int adjusted_mana_amount = min(mana_amount, maxmana - currentmana);
    
    // Using the calculate_heal_amount results in a 400% increase in 
    // mana regeneration at 25% combat aid. 
    // Will limit mana regeneration to 25% increase, so adjust_mana_amount
    // will be divided by 400 and multipled by 125.

    adjusted_mana_amount = (adjusted_mana_amount * 125) / 400;
    
    // Earth branch has 50% CAID instead of 25% so double the results
    if (GUILD_MANAGER->query_primary_element(target) == "earth")
    	adjusted_mana_amount += adjusted_mana_amount;
    
    target->add_mana(adjusted_mana_amount);
    if (mana_amount == adjusted_mana_amount)
    {
        send_debug_message("regeneration_obj", "Regenerating "
                           + adjusted_mana_amount + " mana point(s).");
    }
    else
    {
        send_debug_message("regeneration_obj", "Regenerating "
                           + adjusted_mana_amount + " mana point(s) instead "
                           + "of " + mana_amount + " because the target has "
                           + "full mana.");
    }
        
    ++Heal_number;
    
    // Only notify if the notification interval has passed
    if (Notify_timestamp + ftoi(NOTIFICATION_INTERVAL) < time())
    {
        hook_describe_regeneration(target, mana_amount);
        Notify_timestamp = time();
    }
}
*/