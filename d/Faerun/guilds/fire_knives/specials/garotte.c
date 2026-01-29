/*
 * Garotte combat special for the Fire Knives
 *
 * Nerull 2019
 *
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit COMBAT_ABILITY_LIB;
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"

#include "../guild.h"

// Prototypes
public void         config_ability();
static int          check_valid_action(object player, mixed *targets, 
                                       string arg, int execute);

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_name("garrote");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(2);
    set_ability_cooldown_time(108);
    set_ability_offensive(1);
    set_ability_target(target_one_other_present_living_or_enemy);
}


string
query_component()
{
    return "garotte_wire";
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
    
    enemy = targets[0];

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (FIREKNIVES_MAPPINGS->query_ability1(player->query_name()) == 0)
    {
        player->catch_tell("What?\n");
        
        return 0;
    }

    if (!player->query_skill(SS_ART))
    {
        player->catch_tell("You are not skilled the Arts of Assassination!\n");

        return 0;
    }
   
    if (enemy->query_prop(LIVE_I_UNDEAD))
    {
        player->catch_tell("The dead cannot be silenced by this method!\n");

        return 0;
    }
    
    if (present("_blind_cooldwn_obj", player))
    {
        player->catch_tell("Your target is either blinded already or "
        +"is still recovering from the effect and is therefore "
        +"not eligible for garrote yet!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garrote of the "
        +"target, garrote is not yet ready to be used! Patience!\n");

        return 0;
    }
	
	if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, garrote is not yet ready to be used! Patience!\n");

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
        player->catch_msg("You are preparing to garrote your opponent!\n");
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
        player->catch_msg("You have no proper wire "
        +"to execute garrote!\n");
        return 0;
    }     

    // If it passes everything, return success
    return 1;
}


static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You prepare to strangle your opponent with a garrote.\n");
}


public void
resolve_combat_special(object actor, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    object  enemy,
            effect_obj;
            
    object *obb;
    
    string  taunt,
            message,
            player_msg,
            enemy_msg,
            watcher_msg;
    
    enemy   = target;
              
    // Garotte component
    obb = filter(deep_inventory(actor),
    &operator(==)(query_component()) @&->query_name());

    // This should never happen.
    if (!sizeof(obb))
    {
        actor->catch_msg("Too late you realize you have no proper wire "
        +"to execute garrote!\n");
        return;
    }

    // Random chance for a wire to break / be consumed
    if (random(6) == 1)
    {
        obb[0]->reduce_heap_size(); 
        
        actor->catch_msg("Your garrote wire breaks!\n");
    }        
    
    if (result > 0)
    {
        actor->catch_msg("You quickly sidestep around your "
        +"enemy catching "+enemy->query_possessive()
        +" neck with your left hand and "
        +"dance around his back while reaching towards your "
        +"left with your right hand to pull a string from it "
        +"which you tighten around "+QTPNAME(enemy)+" neck, "
        +"choking "+enemy->query_objective()+".\n");

        enemy->catch_msg(QCTNAME(actor)+ " quickly sidesteps "
        +"around you, catching your neck with "
        +actor->query_possessive()+" left hand "
        +"and dancing around your back while reaching towards "
        +actor->query_possessive()+" left with "
        +actor->query_possessive()+" right hand "
        +"to pull a string from "
        +"it which tightens around your neck, choking you, "
        +"leaving you gasping for breath.\n");

        actor->tell_watcher(QCTNAME(actor) +" quickly sidesteps "
        +"around "+QTNAME(enemy)+", catching "
        +enemy->query_possessive()+"'s neck "
        +"with " +actor->query_possessive()+" left hand and dancing "
        +"around "+QTPNAME(enemy)+" back while reaching towards "
        +actor->query_possessive()+" left with "
        +actor->query_possessive()+" right hand to pull a string from it which "
        +"tightens around "+enemy->query_possessive()+"'s neck, cutting "
        +"off "+enemy->query_possessive()+" breath, leaving "
        +enemy->query_possessive()+" gasping in agony while "
        +"trying to breathe.\n", 
        enemy, ({ actor, enemy }));
        
       
        setuid();
        seteuid(getuid());
            
        effect_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/garotte_obj");
        
        effect_obj->move(enemy);
        effect_obj->start();
    }
    else
    {
        actor->catch_msg("You try to sidestep around your enemy "
        +"to choke "+enemy->query_possessive()+", but are too "
        +"slow and are stopped in your "
        +"tracks.\n");

        enemy->catch_msg(QCTNAME(actor)+" tries to sidestep around "
        +"your defenses, but you are faster and stop "
        +actor->query_possessive()+".\n");

        actor->tell_watcher(QTNAME(actor)+" tries to sidestep around "
        +enemy->query_possessive+"'s defenses but is too slow and is "
        +"stopped in "+actor->query_possessive()+" tracks.\n", 
        enemy, ({ actor, enemy }));
    }
}


public void
hook_special_complete()
{
    write("You feel ready to execute garrote or any other primary ability again.\n");
}


public void
hook_already_active(object ability)
{
    write("You are already preparing to garrote someone!\n");
}


public void
hook_special_in_cooldown()
{
    write("You're not ready garrote someone yet.\n");
}


