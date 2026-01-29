/*
 * Disarm Object - based on the Elementalists disarm spell object
 * by Jaacar, February 2017.
 *
 * For weapons that are imbued, it disarms for a limited duration
 * rather than breaking the weapon.
 *
 * Created by Arman, April 2020.
 *
 * Updated July 2022 - Zizuph.  Ported to new disable attack effect.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "disable_attack_obj";

public void
hook_attack_blocked(object player, int attack_id, object weapon)
{
    player->catch_msg("You try to swing your " + weapon->query_short() +
        ", but the pain in your hand prevents you from doing so.\n");
   
    tell_room(environment(player), QCTNAME(player) + " winces as "
        + player->query_pronoun() + " tries to swing " 
        + player->query_possessive()
        + " " + weapon->query_short() + ".\n", ({ player }));
}

public void
hook_disable_attack_begin(object caster, object target)
{
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your hands.\n");        
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been temporarily "+
            "disarmed!\n");
    }
 }

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_disable_attack_ended(object target)
{
    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The pain in your hands subside.\n");
    }

    if (objectp(query_effect_caster()) && objectp(target) 
        && environment(query_effect_caster()) == environment(target))
    {
        query_effect_caster()->catch_msg(QCTNAME(target) + " seems "
            + "to be able to use weapons again.\n");
    }        
}
