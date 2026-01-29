/*
 * Water Shield for the Schirmo Spell for the Elementalists of Calia
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
inherit SPELL_OBJ_DIR + "regeneration_obj";

// Defines
#define NOTIFICATION_INTERVAL   30.0
#define WATERSHIELD_SUBLOC "_watershield_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_schirmo_water_object_");
    set_short("schirmo water shield object");    
    set_long("This is the schirmo water shield object. It regenerates "
        + "the caster's health.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the schirmo elemental shield spell.\n");
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("schirmo water shield");    
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
    
    string caster_message = "As you complete your prayer to Lord Diabrecho, "
        + "you sense the water in the air stir as he grants his "
        + "revitalizing water for your use. ";
    string target_message = "Filaments of water appear out of nowhere and "
        + "coalesce around you until the water surrounds your entire body, "
        + "forming a thin regenerative layer of water upon your skin.\n";
    string watcher_message = "Filaments of water appear out of nowhere and "
        + "coalesce around " + QTNAME(target) + " until the water surrounds "
        + target->query_possessive() + " entire body, forming a thin "
        + "layer of water upon " + target->query_possessive() + " skin.\n";
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
    
    target->catch_tell("The life sustaining layer of water upon your skin "
        + "dissipates, leaving you a bit chilled.\n");
    tell_room(environment(target), "The translucent layer of water upon "
        + QCTPNAME(target) + " skin dissipates, leaving " 
        + target->query_objective() + " a bit chilled.\n", ({ target }));
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
    
    target->catch_tell("You sense the cohesion in the layer of water upon "
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
            + "the schirmo gift of Lord Diabrecho.\n");
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
        target->catch_tell("The life sustaining layer of water thickens "
            + "around your wounds, speeding up your recovery.\n");
        break;
    
    default:
        target->catch_tell("You feel the chilled liquid of translucent "
            + "layer of water moving across your injuries, healing "
            + "them.\n");
        break;
    }       
}

/*
 * Function:    query_watershield_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_watershield_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "A translucent life sustaining layer of water closely "
            + "wraps your body.\n";
    else
        return capitalize(on->query_pronoun()) + " has a translucent "
            + "layer of water upon " + on->query_possessive()
            + "skin.\n";
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
        to->add_subloc(WATERSHIELD_SUBLOC, this_object());        
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
        old->remove_subloc(WATERSHIELD_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != WATERSHIELD_SUBLOC)
    {
        return "";
    }
    
    return query_watershield_subloc_description(on, for_obj);
}

