#pragma strict_types

#include "/d/Genesis/specials/defs.h"
#include "../guild.h"
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

inherit DEBUFF_LIB;


/*
 * Function Name:   hook_blind_begin
 * Description:     The text displayed when the blind begins.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the blind
 *                  (status) 1 - target is already blinded
 *                           0 - target is not previously blinded
 * Returns:         Nothing
 */
public void
hook_blind_begin(object actor, object target, status blinded)
{
    target->catch_msg("Your eyes soar in pain as the powder in them starts "
    + "to boil!" + (blinded ? "" : "\nYou are blinded!") + "\n");
    
    tell_room(environment(target), QCTNAME(target) + " screams in pain as "
    + target->query_possessive() + " eyes seems to start boiling!\n", target);  
} /* hook_blind_begin */

/*
 * Function Name:   hook_blind_ended
 * Description:     The text displayed when the blind ends.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the blind
 *                  (status) 1 - target is still blinded
 *                           0 - target is no longer blinded
 * Returns:         Nothing
 */
public void
hook_blind_ended(object actor, object target, status blinded)
{
    if (!blinded)
    {
        target->catch_msg("The searing pain in your eyes fades away, and you "
        + "regain most of your vision.\n");
    
        tell_room(environment(target), QCTNAME(target) + " seems to regain "
        + target->query_possessive() + " most of the vision again.\n", target);
        return;
    }
    
    // Blind can stack, so if your target is still affected you can print
    // further messages here.
} /* hook_blind_ended */

public object
setup_blind_effect(object actor, object target, mixed *items, int resist)
{
    object effect;
    
    effect = clone_object(BLIND_OBJ_BASE);
    
    effect->set_hook_blind_begin(hook_blind_begin);
    effect->set_hook_blind_ended(hook_blind_ended);
    
    return effect;
} /* setup_blind_effect */

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_ability()
{
    ::config_ability();
    set_ability_prep_time(2);
    set_ability_cooldown_time(108);
    set_ability_name("blind");
    
    set_tohit(110);
    set_stats(({ TS_WIS }));
    set_skills(({ SS_ART }));
    set_combat_aid(90);
    
    // Set this to a function so we could add a hook for when the blind ends.
    set_debuff_effect(setup_blind_effect);
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
} /* config_ability */

/*
 * Function name:   resolve_debuff_ability
 * Description:     This function is called from resolve_ability to finalize
 *                  the special.
 *
 * Arguments:       1. (object)   The actor
 *                  2. (object *) The targets
 *                  3. (int *)    Resistance values corresponding to each target
 *                  4. (int)      The attempt result as returned by
 *                                query_casting_success()
 *
 * Returns:         Nothing
 */
public void
resolve_debuff_ability(object actor, mixed *items, mixed *targets, int *resist,
                       mixed *result)
{
    object enemy = targets[0];
    
    if (result[0] > 0)
    {
        actor->catch_msg("You take a small pinch of red powder from "
        +"your belongings and blow it on "+QTPNAME(enemy)+" eyes!\n");
        
        enemy->catch_msg(QCTNAME(actor)+" takes out a "
        +"small pinch of red powder from "
        +actor->query_possessive()+" belongings and blows it "
        +"on your eyes!\n");
            
        actor->tell_watcher(QCTNAME(actor)
        +" takes a small pinch of red powder from "
        +actor->query_possessive()+" belongings and blows it on "
        +QTPNAME(enemy)+" eyes!\n",enemy, ({ actor, enemy }));      
    }
    else
    {
        actor->catch_msg("You take out a small pinch of red powder from your "
        + "belongings and try to blow it on " + QTPNAME(enemy) + " eyes, but "
        + "you miss.\n");
            
        enemy->catch_msg(QCTNAME(actor)+" takes out a small pinch of "
        +"red powder from "+actor->query_possessive()+" belongings and "
        +"attempts to blow it on "+QTPNAME(enemy)+" eyes but misses.\n");
        
        actor->tell_watcher(QTNAME(actor)+" takes out a small pinch of red "
        +"powder from "+actor->query_possessive()+" belongings and attempts "
        +"to blow it on your eyes, but misses.\n", enemy, ({ actor, enemy }));
    }
} /* resolve_debuff_ability */

public void
hook_special_complete()
{
    write("You feel ready to execute blind or any other primary ability "
    + "again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are already preparing to blind someone!\n");
}

public void
hook_special_in_cooldown()
{
    write("You're not ready blind someone yet.\n");
}

static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You prepare to blind your target.\n");
}

string
query_component()
{
    return "blinding_powder";
}

/*
* Function name: check_valid_action
* Description:   Perform ability-specific checks
* Arguments:     1. (object) The player
*                2. (mixed *) The targets
*                3. (string) Arguments passed to the command
*                4. (int) Actual spell execution
* Returns:       (int) 1 if we can continue, 0 if failure
*/
static int
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;
    object * enemies;
    
    object blind_token;
    object silence_token;
        object stun_token;
    
   // object *obb;
    
    enemy = targets[0];

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(player->query_name()) < AB5)
    {
        player->catch_tell("You are not qualified to use this ability.\n");
        
        return 0;
    }

    if (!player->query_skill(SS_ART))
    {
        player->catch_tell("You are not skilled the arts of Assassination!\n");
        return 0;
    }
    
    if (enemy->query_prop(LIVE_I_UNDEAD))
    {
        player->catch_tell("The dead cannot be blinded by this method!\n");

        return 0;
    }
    
    if (present("_blind_cooldwn_obj", player))
    {
        player->catch_tell("Your target is either blinded already or "
        +"is still recovering from the effect and is therefore "
        +"not eligible for blind yet!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garotte of the "
        +"target, blind is not yet ready to be used! Patience!\n");

        return 0;
    }
        
        if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, blind is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (STUN_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing your stun your opponent!\n");
        return 0;
    }
    
    if (EVADE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to evade your opponent!\n");
        return 0;
    }
    
    if (BLIND_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to blind your opponent!\n");
        return 0;
    }
    
    if (EVISCERATE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to eviscerate!\n");
        return 0;
    }
    
    if (BACKSTAB_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to backstab!\n");
        return 0;
    }
    
    if (GAROTTE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to garotte your opponent!\n");
        return 0;
    }
    
    if (STUN_ABILITY->query_ability_in_cooldown(player)
        || BLIND_ABILITY->query_ability_in_cooldown(player)
        || GAROTTE_ABILITY->query_ability_in_cooldown(player)
        || BACKSTAB_ABILITY->query_ability_in_cooldown(player)
        || EVADE_ABILITY->query_ability_in_cooldown(player)
        || EVISCERATE_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("You are not yet ready to do that!\n");
        return 0;
    }
    
    if (player->query_alignment() > -10)
    {
        player->catch_msg("You struggle with your conscience to execute "
        +"such an action!\n");
        return 0;
    }
    
    // Blind component
    object *obb;
    
    obb = filter(deep_inventory(player),
    &operator(==)(query_component()) @&->query_name());

    if (!sizeof(obb))
    {
        player->catch_msg("You do not have blinding powder to blind your opponent!\n");
        
        return 0;
    } 

    // If it passes everything, return success
    return 1;
}