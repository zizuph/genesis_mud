
#include <cmdparse.h>
#include <macros.h>

public int filter_unbrawled_and_present(object actor, object target)
{
    if (!target || !actor)
    {
        return 0;
    }
    if (environment(target) != environment(actor))
    {
        return 0;
    }
    foreach(object effect : target->query_blind_effects())
    {
        if (effect->query_effect_caster() == actor)
        {
            return 0;
        }
    }

    foreach(object effect : target->query_stun_effects())
    {
        if (effect->query_effect_caster() == actor)
        {
            return 0;
        }
    }
    
    foreach(object effect : target->query_disable_attack_effects())
    {
        if (effect->query_effect_caster() == actor)
        {
            return 0;
        }
    }
    return 1;
}

public int filter_unbrawled_and_present_and_armed(object actor, object target)
{
    if (!filter_unbrawled_and_present(actor, target))
        return 0;
    if (sizeof(target->query_weapon(-1)))
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: target_one_present_unbrawled_enemy
 */
public object *
target_one_present_unbrawled_enemy(object actor, string str)
{
    object* active_abilities = this_object()->query_active_abilities(
      actor, this_object()->query_ability_group());
    if (sizeof(active_abilities))
    {
        // No other active abilities. We can safely start this ability
        actor->catch_tell("You are still focused on your " +
          "attempt to " + active_abilities[0]->query_ability_name() + ".\n");
        return 0;
    }

    return this_object()->target_one_other_present_living_or_unaffected_enemy(
        filter_unbrawled_and_present, actor, str);
}

/*
 * Function name: target_one_present_unbrawled_armed_enemy
 */
public object *
target_one_present_unbrawled_armed_enemy(object actor, string str)
{
    object* active_abilities = this_object()->query_active_abilities(
      actor, this_object()->query_ability_group());
    if (sizeof(active_abilities))
    {
        actor->catch_tell("You are still focused on your " +
        "attempt to " +  active_abilities[0]->query_ability_name() + ".\n");
        return 0;
    }
    return this_object()->target_one_other_present_living_or_unaffected_enemy(
        filter_unbrawled_and_present_and_armed, actor, str);
    
}
