/*
 * Standard Light Object
 *
 * This is the spell object for the standard Genesis Magic System Light
 * spell. It provides light as a duration spell effect, and continually
 * drains mana.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";

#define LIGHT_SUBLOC        "_light_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_light_object_");
    set_short("light spell object");    
    set_long("This is the standard light spell's object. It emits "
        + "light.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the light spell.\n");
    set_spell_effect_desc("light");
    
    // 15 minutes
    // set_dispel_time(900);
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
    int light_bonus;

    if (!result)
    {
        return result;
    }

    int power = query_spell_effect_power();

    light_bonus = min(5, max(1, (power - 220) / 30));

    // Int/wis of 100, spell skills 20 / 50 / 75 / 100
    //             spell power:  269 / 284 / 302 / 317
    //             light bonus:   1 / 2 / 2 / 3

    // Int/wis of 200, spell skills  50 / 75 / 100
    //             spell power:    348 / 364 / 384 
    //             light bonus:     4 / 4 / 5

    // Max level 5 light based on spell power and mental stats

    add_prop(OBJ_I_LIGHT, light_bonus);
    environment(this_object())->update_light(1);

    //query_effect_target()->catch_msg("Spell power: "+power+".\n");
    //query_effect_target()->catch_msg("Light: "+light_bonus+".\n");
    
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
    
    remove_prop(OBJ_I_LIGHT);
    environment(this_object())->update_light(1);

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
        target->catch_tell("Your surroundings are illuminated with light.\n");
        tell_room(environment(target), "Your surroundings are " +
            "illuminated with light.\n", ({ target }));
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The light surrounding you fades.\n");
        tell_room(environment(target), "The light surrounding "
            + QTNAME(target) + " fades.\n", ({ target }));
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
        target->catch_tell("You sense the intensity of the light surrounding "
            + "you begin to wane.\n");
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
            + "the light surrounding you.\n");
    }    
}

/*
 * Function:    query_light_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_light_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are illuminated by a magical light.\n";
    else
        return capitalize(on->query_pronoun()) + " is illuminated by " +
                "a magical light.\n";
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
        to->add_subloc(LIGHT_SUBLOC, this_object());        
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
        old->remove_subloc(LIGHT_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    return query_light_subloc_description(on, for_obj);
}
