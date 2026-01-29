/*
 * Standard Blind Object
 *
 * This is the spell object for the standard Genesis Magic System's
 * blind spell. It blinds the target for a limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Navarre, March 2010.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

private object effect_obj;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_blind_object_");
    set_short("blind spell object");    
    set_long("This is the standard blind spell object. " +
             "It blinds the target.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the blind spell.\n");
    set_spell_effect_desc("blind");
    
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

    effect_obj = clone_object(SPELL_OBJ_DIR + "blind_effect_obj");
    effect_obj->set_effect_caster(query_spell_effect_caster());
    effect_obj->set_effect_target(query_spell_effect_target());
    effect_obj->set_effect_stats(query_spell_stats());
    
    // This is not correct, the skills may not be sup guru.
    // Removing for now, until a proper skill check can be added.
    // effect_obj->set_effect_skills(get_default_spell_skills());    
    effect_obj->set_short(query_spell_effect_name() + " effect object");
    effect_obj->set_long(query_spell_effect_desc());
    
    mapping input = query_spell_effect_input();
    
    float resistance = 0.0;
    int target_count = 1;
    if (mappingp(input))
    {
        int tohit = input["tohit"];
        effect_obj->set_blind_tohit(tohit);
        resistance = input["resistance"];
        target_count = max(input["targets"], 1);
        send_debug_message("debug_blind",
            sprintf("Resistance : %f, tohit: %d, target count %d", 
            resistance, tohit, target_count));
    }
    else
    {
        send_debug_message("debug_blind",
            "Mapping for blind is missing.");
    }
    effect_obj->set_blind_chance(100);
    send_debug_message("debug_blind",
        sprintf("Starting combat aid : %f", query_spell_combat_aid()));

    // Apply increase in CAID due to innate resistance here.
    int combat_aid = ftoi(query_spell_combat_aid() * 100.0 / (100.0 - resistance));

    // Split the aid based on the number affected.
    combat_aid = combat_aid / target_count;
    
    send_debug_message("debug_blind",
        sprintf("Final combat aid : %d", combat_aid));
    effect_obj->set_blind_combat_aid(combat_aid);
    effect_obj->move(query_effect_target(), 1);
    effect_obj->set_spell_effect_object(this_object());
    effect_obj->start();

    // This effect is normally over in 30s, bud other blinds may
    // cause it to last longer.
    set_dispel_time(120);

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
    query_effect_target()->remove_blind_effect(effect_obj);
    return 1;
}

public void
hook_spell_effect_started()
{
    // Messages are done through hook_blind_begin and hook_blind_ended now.
}

public void
hook_spell_effect_ended()
{
    // Messages are done through hook_blind_begin and hook_blind_ended now.
}


/*
 * Function:    hook_blind_begin
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_blind_begin(object actor, object target, object *effects)
{    
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your eyes.\nYou have been blinded!\n");
    }
    
    if (objectp(actor) && objectp(target))
    {
        actor->catch_msg(QCTNAME(target) + " has been blinded!\n");
    }
}

/*
 * Function:    hook_blind_failed
 * Description: Override this to customize the message when this spell effect
 *              could not take effect.
 */
public void hook_blind_failed(object actor, object target)
{
    if (objectp(actor))
    {
        actor->catch_msg("Your attempt to blind " + QTNAME(target) + 
            "has failed.\n");
    }
}

/*
 * Function:    hook_blind_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_blind_ended(object actor, object target, object *effects)
{
    if (objectp(target))
    {
        target->catch_tell("The pain in your eyes subside.\n");
    }

    if (objectp(actor))
    {
        actor->catch_msg(QCTNAME(target) + " blinks a few times and seems "
            + "to be able to see again.\n");
    }
}
