/*
 * effect_object.c
 *
 * All abilities which have lasting effects that can be listed
 * or dispelled should create spell effect object which
 * inherits this file.
 *
 *
 */

#pragma strict_types

static object effect_caster;
static mixed  effect_target;
static string effect_name, effect_desc;

static int alarm_id;

public void remove_effect_object();

/*
 * Function name: set_effect_name
 * Description:   Set the name of the effect.  This should
 *                generally be the name of the effect itself.
 * Arguments:     string name - the name of the effect
 */
public void
set_effect_name(string name)
{
    effect_name = name;
}

public string
query_effect_name()
{
    return effect_name;
}

/*
 * Function name: set_effect_desc
 * Description:   Set the description of the effect.  This
 *                should be a short, one or two word description:
 *                "invisibility" or "night vision", for instance.
 * Arguments:     string desc - the effect description
 */
public void
set_effect_desc(string desc)
{
    effect_desc = desc;
}

public string
query_effect_desc()
{
    return effect_desc;
}


/*
 * Function name: set_effect_caster
 * Description:   Designate the origin of the effect, the
 *                caster of the ability.
 * Arguments:     object caster - the spell caster
 */
public void
set_effect_caster(object caster)
{
    effect_caster = caster;
}

public object
query_effect_caster()
{
    return effect_caster;
}

/*
 * Function name: set_effect_target
 * Description:   Designate the target of the effect
 * Arguments:     object target - the target
 */
public void
set_effect_target(mixed target)
{
    effect_target = target;
}

public mixed
query_effect_target()
{
    return effect_target;
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

/*
 * Function name: setup_effect
 * Description;   Sets up the ability effect.  This makes sure that
 *                the effect has properly started and removes if it
 *                not.
 * Returns:       1/0 - effect set up
 */
public int
setup_effect()
{
    if (!start())
    {
        remove_effect_object();
	return 0;
    }

    return 1;
}

/*
 * Function name: set_dispel_time
 * Description;   Creates a timer that will dispel the effect
 * Arguments:     i - number of seconds before the effect vanishes                
 * Returns:       none
 */
public void set_dispel_time(int i)
{
    if (alarm_id)
    {
        remove_alarm(alarm_id);
        alarm_id=0;
    }
    alarm_id=set_alarm(itof(i),0.0,&dispel_effect(0));
}


/*
 * Function name: remove_effect_object
 * Description:   Remove the spell effect object, unregistering it as
 *                well.
 */
public void
remove_effect_object()
{
    destruct();
}

/*
 * Function name: query_effect_object
 * Description:   Easy way to tell if this object is a spell effect
 *                object
 * Returns:       1
 */
public int
query_effect_object()
{
    return 1;
} 
