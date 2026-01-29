#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

public int
valid_attack_id(object combat_object, int attack_id)
{
    if (attack_id == -1)
    {
        return 0;
    }
    
    if (!sizeof(combat_object->query_attack(attack_id)))
    {
        // The combat object doesn't recognize this attack id
        return 0;
    }
    
    return 1;
}

void
spike_damage(object target, int pen)
{
    target->hit_me(pen, W_IMPALE, shadow_who, -1);
    target->catch_msg("You hurt yourself on the steel-spiked helm.\n");
    tell_room(environment(shadow_who), QCTNAME(target)+" is hurt by the steel-spiked helm!\n", target);

    if (target->query_hp() < 1)
    {
        target->do_die(shadow_who);
    }

}

varargs mixed
hit_me(int wcpen,
       int dt,
       object attacker,
       int attack_id,
       int target_hitloc = -1)
{

    mixed returnValue;
    
    object combat_object = attacker->query_combat_object();
    if (wcpen < 0 || !valid_attack_id(combat_object, attack_id))
    {
        return shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    }

    returnValue = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);    
    if(returnValue)
    {
        target_hitloc = returnValue[4];
    }

    if (target_hitloc == A_HEAD)
    {
        combat_object->cb_did_hit(attack_id, returnValue[1], returnValue[4], returnValue[0], 
               shadow_who, dt, 100, returnValue[3]);

        if (returnValue[0] > 0)
        {
            /* Need to run this from an alarm to prevent runtimes */
            set_alarm(0.0, 0.0, &spike_damage(attacker, min(50 + random(100), wcpen)));
        }

        /* Prevent default combat message */
        returnValue[1] = 0;
    }
    return returnValue;
}


void
remove_helm_shadow()
{
    remove_shadow();
}
