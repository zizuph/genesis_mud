
/*
 * Built-in spell targeting functions
 */

#include "defs.h"
inherit ABILITY_DIR+"targetting";

#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>

/*
 * Function name: spell_target_actor
 * Description:   Target an ability on the actor
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets (the actor)
 */
public object *
spell_target_caster(object actor, string str)
{
    return target_actor(actor,str);
}

public object *
spell_target_caster_environment(object actor, string str)
{
    return target_actor_environment(actor, str);
}

public object *
spell_target_one_present_enemy(object actor, string str)
{
    return target_one_present_enemy(actor,str);
}

public object *
spell_target_present_enemies(object actor, string str)
{
    return target_present_enemies(actor,str);
}

public object *
spell_target_present_team(object actor, string str)
{
    return target_present_team(actor,str);
}

public object *
spell_target_present_team_others(object actor, string str)
{
    return target_present_team_others(actor,str);
}

public object *
spell_target_one_present_living(object actor, string str)
{
    return target_one_present_living(actor,str);
}

public object *
spell_target_present_livings(object actor, string str)
{
    return target_present_livings(actor,str);
}
    
public object *
spell_target_one_other_present_living(object actor, string str)
{
    return target_one_other_present_living(actor,str);
}

public object *
spell_target_one_other_present_living_or_enemy(object actor, string str)
{
    return target_one_other_present_living_or_enemy(actor,str);
}

public object *
spell_target_one_present_non_living(object actor, string str)
{
    return target_one_present_non_living(actor,str);
}

public object *
spell_target_one_present_non_living_or_wielded_weapon(object actor, string str)
{
    if (strlen(str))
    {
        return target_one_present_non_living(actor,str);
    }
    return target_wielded_weapon(actor, str);
}

/*
 * Function name: spell_target_present_non_livings
 * Description:   Target an ability on multiple non_living object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_present_non_livings(object actor, string str)
{
    return target_present_non_livings(actor,str);
}

/*
 * Function name: spell_target_one
 * Description:   Target an ability on one object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_present_object(object actor, string str)
{
    return target_one_present_object(actor,str);
}

/*
 * Function name: target
 * Description:   Target an ability on mutiple objects
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_present_objects(object actor, string str)
{
    return target_present_objects(actor,str);
}

/*
 * Function name: spell_target_one_distant_known_living
 * Description:   Target an ability on living known to the actor
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_distant_known_living(object actor, string str)
{
    return target_one_distant_known_living(actor,str);
}

/*
 * Function name: spell_target_one_distant_living
 * Description:   Target an ability on a living in the game
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_distant_living(object actor, string str)
{
    return target_one_distant_living(actor,str);
}

    
public object *
spell_verify_present(object actor, object *targets, string arg)
{
    return filter(targets, &filter_present(, actor));
}

