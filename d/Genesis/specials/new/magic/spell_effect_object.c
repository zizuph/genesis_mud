/*
 * spell_effect_object.c
 *
 * All spells which have lasting effects that can be listed
 * or dispelled should create spell effect object which
 * inherits this file.
 *
 * It is suggested that spell effect objects be created using
 * make_spell_effect_object() in spell_config.c.  This function
 * will automatically handle much of the configuration of spell
 * effect objects, provided that you use the rest of the
 * functionality provided in spell_config.c.
 * The one important configuration item that is not handled by
 * make_spell_effect_object() is setting the description of the
 * spell effect, which should be done by calling
 * set_spell_effect_desc() with a string argument which gives
 * a simple, one or two word description of the spell effect.
 * For instance, the effect description for an invisibility
 * spell would be "invisibility"; the description for a spell
 * that gives LIVE_I_SEE_DARK might be "night vision".
 *
 * Fix logic on moving the spell effect to its destination if
 * it is a valid container.
 * Zizuph July 2022
 *
 */

#pragma strict_types

#include "defs.h"
#include <tasks.h>
inherit ABILITY_DIR+"effect_object";

int spell_form, spell_element, spell_power;

float spell_combat_aid = 0.0;
float spell_maintained_combat_aid = 0.0;
int spell_task;
int spell_effect_class;
mixed spell_stats;
mixed spell_skills;

public void remove_spell_effect_object();

/*
 * Function name: set_spell_effect_name
 * Description:   Set the name of the spell effect.  This should
 *                generally be the name of the spell itself.
 * Arguments:     string name - the name of the effect
 */
public void
set_spell_effect_name(string name)
{
    set_effect_name(name);
}

public string
query_spell_effect_name()
{
    return query_effect_name();
}

/*
 * Function name: set_spell_effect_desc
 * Description:   Set the description of the spell effect.  This
 *                should be a short, one or two word description:
 *                "invisibility" or "night vision", for instance.
 * Arguments:     string desc - the effect description
 */
public void
set_spell_effect_desc(string desc)
{
    set_effect_desc(desc);
}

public string
query_spell_effect_desc()
{
    return query_effect_desc();
}

/*
 * Function name: set_spell_effect_element
 * Description:   Set the spell effects magic element (SS_ELEM_*).
 *                This should be the same element as used by the
 *                spell.
 * Arguments:     int elem - the element (skill)
 */
public void
set_spell_effect_element(int elem)
{
    spell_element = elem;
}

public int
query_spell_effect_element()
{
    return spell_element;
}

/*
 * Function name: set_spell_effect_form
 * Description:   Set the spell effects magic form (SS_FORM_*).
 *                This should be the same form as used by the
 *                spell.
 * Arguments:     int elem - the form (skill)
 */
public void
set_spell_effect_form(int form)
{
    spell_form = form;
}

public int
query_spell_effect_form()
{
    return spell_form;
}

/*
 * Function name: set_spell_effect_power
 * Description:   Set the "power" of the spell effect.  This is
 *                essentially how difficult the spell effect is
 *                to dispel, and should be a value 0 - 100, higher
 *                values being harder to dispel.
 * Arguments:     int power - the power of the effect
 */
public void
set_spell_effect_power(int power)
{
    spell_power = power;
}

public int
query_spell_effect_power()
{
    return spell_power;
}

/*
 * Function name: set_spell_effect_caster
 * Description:   Designate the origin of the spell effect, the
 *                caster of the spell.
 * Arguments:     object caster - the spell caster
 */
public void
set_spell_effect_caster(object caster)
{
    set_effect_caster(caster);
}

public object
query_spell_effect_caster()
{
    return query_effect_caster();
}

/*
 * Function name: set_spell_effect_target
 * Description:   Designate the target of the spell effect
 * Arguments:     object target - the target
 */
public void
set_spell_effect_target(mixed target)
{
    set_effect_target(target);
}

public mixed
query_spell_effect_target()
{
    return query_effect_target();
}

/*
/*
 * Function name: dispel_spell_effect
 * Description:   Cause this spell effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_spell_effect(object dispeler)
{
    return 1;
}

/*
/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    if (!dispel_spell_effect(dispeler))
    {
        return 0;
    }
    return ::dispel_effect(dispeler);
}



public int
setup_spell_effect()
{
    effect_target->add_magic_effect(this_object());
    return setup_effect();
}

/*
 * Function name: remove_spell_effect_object
 * Description:   Remove the spell effect object, unregistering it as
 *                well.
 */
public void
remove_spell_effect_object()
{
    effect_target->remove_magic_effect(this_object());
    remove_effect_object();
}

/*
 * Function name: query_spell_effect_object
 * Description:   Easy way to tell if this object is a spell effect
 *                object
 * Returns:       1
 */
public int
query_spell_effect_object()
{
    return 1;
} 

/*
 * Function name: query_spell_combat_aid
 * Description:   How much combat aid the spell provided
 *                
 * Returns:       The combat aid provided by the spell
 */
public float
query_spell_combat_aid()
{
    return spell_combat_aid;
}

/*
 * Function name: set_spell_maintained_combat_aid
 * Description:   Specify how much combat aid the spell provided
 */
public void 
set_spell_maintained_combat_aid(float aid)
{
    spell_maintained_combat_aid = aid;
}

/*
 * Function name: query_spell_maintained_combat_aid
 * Description:   How much combat aid the spell provided
 *                
 * Returns:       The combat aid provided by the spell
 */
public float
query_spell_maintained_combat_aid()
{
    return spell_maintained_combat_aid;
}

/*
 * Function name: set_spell_combat_aid
 * Description:   Specify how much combat aid the spell provided
 */
public void 
set_spell_combat_aid(float aid)
{
    spell_combat_aid = aid;
}


/*
 * Function name: query_spell_task
 * Description:   The difficulty of the task from the spell
 *                
 * Returns:       The difficulty used by the spell.
 */
public int
query_spell_task()
{
    return spell_task;
}

/*
 * Function name: set_spell_task
 * Description:   Specify how difficult the task was.
 */
public void 
set_spell_task(int task)
{
    spell_task = task;
}

/*
 * Function name: query_spell_stats
 * Description:   The stats used to power the spell.
 *                
 * Returns:       The stats used by the spell.
 */
public mixed
query_spell_stats()
{
    return spell_stats;
}

/*
 * Function name: set_spell_stats
 * Description:   Specify which stats were used for the spell
 */
public void 
set_spell_stats(mixed stats)
{
    spell_stats = stats;
}

/*
 * Function name: query_spell_skills
 * Description:   The skills used to power the spell.
 *                
 * Returns:       The skills used by the spell.
 */
public mixed
query_spell_skills()
{
    return spell_skills;
}

/*
 * Function name: set_spell_skills
 * Description:   Specify which skills were used for the spell
 */
public void 
set_spell_skills(mixed skills)
{
    spell_skills = skills;
}


/*
 * Function name: query_spell_effect_class
 * Description:   The spell class of the effect.
 *                
 */
public int
query_spell_effect_class()
{
    return spell_effect_class;
}

/*
 * Function name: set_spell_effect_class
 * Description:   Specify the class of the spell effect
 */
public void 
set_spell_effect_class(int class)
{
    spell_effect_class = class;
}
