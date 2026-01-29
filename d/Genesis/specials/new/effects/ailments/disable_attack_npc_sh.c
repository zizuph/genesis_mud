/*
 * disable_attack_npc_sh
 *
 * Created by Zizuph, Dec 2021
 *
 * This ability will allow specific attack IDs from white hits to be
 * blocked.  It works like an evade, but in reverse - preventing a
 * fraction of white hits from being initiated at the source.
 *
 * This version does not mask wield/unwield, as some NPCs have these marked as
 * nomask.
 * 
 *
 */

#pragma strict_types
#pragma save_binary

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>

inherit EFFECT_BASE_SH;
inherit "/d/Genesis/specials/calculations";

// Prototypes
public void         remove_disable_attack_shadow();

public mapping      disable_attack_weapon_shadows = ([]);

/*
 * Function Name:   query_disable_attack_effects
 * Description:     Returns the full list of disable attack effects currently 
                    being kept track of by the effect shadow
 * Arguments:       None
 * Returns:         (object *) An array of disable attack effect objects
 */
public object *
query_disable_attack_effects()
{
    return query_effects();
} /* query_disable_attack_effects */


public int has_disable_attack_shadow()
{
    return 1;
}

public int has_active_disable_effect(int attack_id)
{
    foreach (object effect : query_disable_attack_effects())
    {
        if (effect->query_effect_valid(shadow_who, 0, attack_id))
            return 1;
    }
    return 0;
}

public int
attack_id_blocked(int attack_id, object weapon)
{
    mapping active_effects = ([]);
    int total_aid = 0;
    foreach (object effect : query_disable_attack_effects())
    {
        if (effect->query_effect_valid(shadow_who, 0, attack_id))
        {
          active_effects[effect] = query_effect_combat_aid(({ effect }));

          send_debug_message("disable_attack_sh_debug", 
            "Found a valid effect, caid:" + active_effects[effect]);
          total_aid += active_effects[effect];
        }
    }
    int percentage = query_effect_percentage(m_indexes(active_effects));

    send_debug_message("disable_attack_sh_debug", sprintf(
        "Total aid %d, effective percentage %d", total_aid, percentage));

    mixed* attack = shadow_who->query_combat_object()->query_attack(attack_id);
    // Attack is missing, that is unexpected.
    if (sizeof(attack) < 7)
    {
        return 0;
    }
    if (random(attack[4]) < percentage)
    {
        foreach (object effect : m_indexes(active_effects))
        {
            if (random(total_aid) < active_effects[effect])
            {
                effect->hook_attack_blocked(shadow_who, attack_id, weapon);
                send_debug_message("disable_attack_sh", capitalize(effect->query_name()) 
                    + " caused an blocked attack.");
                return 1;
            }
            else
            {
                total_aid -= active_effects[effect];
            }
        }
        // This should not be able to happen, but this attack was blocked.
        one_of_list(m_indexes(active_effects))->
            attack_blocked(shadow_who, attack_id, weapon);
        return 1;
    }
    return 0;
}

public int
attack_weapon_blocked(object weapon)
{
    foreach (int id : shadow_who->query_combat_object()->query_attack_id())
    {
        mixed* attack = shadow_who->query_combat_object()->query_attack(id);
        if (sizeof(attack) < 7)
            continue;
        if (attack[6] == weapon)
        {
            int result = attack_id_blocked(id, weapon);
            if (result)
                return result;
        }
    }
    return 0;
}


public int add_disable_attack_effect(object effect)
{
    setuid();
    seteuid(getuid());
    
    foreach (object disarm : query_disable_attack_effects())
    {
        // Disarms should not stack on the same target, from the
        // same caster, with the same effect.
        if (disarm->query_effect_caster() == effect->query_effect_caster()
            && MASTER_OB(disarm) == MASTER_OB(effect))
            {
                return 0;
            }
    }
    
    add_effect(effect);
    foreach (object weapon : shadow_who->query_weapon(-1))
    {
        if (!weapon->has_disable_attack_weapon_shadow())
        {
            object weapon_shadow = clone_object(DISABLE_ATTACK_WEAPON_SH);
            weapon_shadow->set_attack_shadow(this_object());
            weapon_shadow->shadow_me(weapon);
            disable_attack_weapon_shadows[weapon] = weapon_shadow;
        }
    }
    return 1;
}

public void remove_disable_attack_effect(object effect)
{
    remove_effect(effect);
    if (!sizeof(query_effects()))
    {
        remove_disable_attack_shadow();
    }
}

public mapping query_disable_attack_weapon_shadows()
{
    return disable_attack_weapon_shadows;
}

/*
 * Function name:   remove_disable_attack_shadow
 * Description:     Handles the removal of effects when removing the shadow.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_disable_attack_shadow()
{
    foreach(object effect : query_effects())
    {
        effect->remove_attack_effect();
    }
    foreach(object shadow : m_values(disable_attack_weapon_shadows))
    {
        shadow->remove_shadow();
    }

    remove_shadow();
} /* remove_disable_attack_shadow */
