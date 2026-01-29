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
 * spell would be "invisibilty"; the description for a spell
 * that gives LIVE_I_SEE_DARK might be "night vision".
 *
 */

#pragma strict_types

static int spell_form, spell_element, spell_power;
static object spell_caster, spell_target;
static string spell_name, spell_desc;

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
    spell_name = name;
}

public string
query_spell_effect_name()
{
    return spell_name;
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
    spell_desc = desc;
}

public string
query_spell_effect_desc()
{
    return spell_desc;
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
    spell_caster = caster;
}

public object
query_spell_effect_caster()
{
    return spell_caster;
}

/*
 * Function name: set_spell_effect_target
 * Description:   Designate the target of the spell effect
 * Arguments:     object target - the target
 */
public void
set_spell_effect_target(object target)
{
    spell_target = target;
}

public object
query_spell_effect_target()
{
    return spell_target;
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
    return 0;
}

/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    return 1;
}

public int
setup_spell_effect()
{
    spell_target->add_magic_effect(this_object());

    if (!start())
    {
        remove_spell_effect_object();
	return 0;
    }

    return 1;
}

/*
 * Function name: remove_spell_effect_object
 * Description:   Remove the spell effect object, unregistering it as
 *                well.
 */
public void
remove_spell_effect_object()
{
    spell_target->remove_magic_effect(this_object());
    destruct();
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
