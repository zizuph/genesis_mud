/*
 * /d/Genesis/sepcials/new/magic/spells/obj/blind_effect_ob
 *
 * This is the actual effect object that causes the blind.  Its role
 * is to interact with the blind spell object, and send it messages
 * so that it may present the relevant text.
 *
 * July 2022, Zizuph: Initial version
 */
 
#include "/d/Genesis/specials/local.h"; 
inherit DISABLE_ATTACK_OBJ_BASE;

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

private object spell_effect_obj;

public object query_spell_effect_object()
{
    return spell_effect_obj;
}

public void set_spell_effect_object(object ob)
{
    spell_effect_obj = ob;
}

public int
remove_shadow_from_list(object obj)
{
    int result = ::remove_shadow_from_list(obj);
    spell_effect_obj->remove_spell_effect_object();
    return result;
}

/*
 * Function     : hook_attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 *                attack_id - attack ID that was blocked
 *                weapon    - weapon in that attack ID, if known.
 * Returns      : nothing
 */
public void
hook_attack_blocked(object player, int attack_id, object weapon)
{
    spell_effect_obj->hook_attack_blocked(player, attack_id, weapon);
}

public void
hook_disable_attack_ended(object player)
{
    spell_effect_obj->hook_disable_attack_ended(player);
}

public void
hook_disable_attack_begin(object attacker, object target)
{
    spell_effect_obj->hook_disable_attack_begin(attacker, target);
}

