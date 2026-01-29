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
    set_ability_name("stun");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(2);
    set_ability_cooldown_time(58);
    set_ability_offensive(1);
    set_ability_target(target_one_other_present_living_or_enemy);
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
    
    if (FIREKNIVES_MAPPINGS->query_ability4(player->query_name()) == 0)
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
        player->catch_tell("The dead cannot be stunned by this method!\n");

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
    
    if (present("_stun_cooldwn_obj", enemy))
    {
        player->catch_tell("Your target is either stunned already or "
        +"is still recovering from the effect and is therefore "
        +"not eligible for stun yet!\n");

        return 0;
    }
    
    if (present("_blind_cooldwn_obj", player))
    {
        player->catch_tell("Your target is either blinded already or "
        +"is still recovering from the effect and is therefore "
        +"not eligible for stun yet!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garotte of the "
        +"target, stun is not yet ready to be used! Patience!\n");

        return 0;
    }
	
	if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, stun is not yet ready to be used! Patience!\n");

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

    // If it passes everything, return success
    return 1;
}


static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You prepare to stun your target.\n");
}


public void
resolve_combat_special(object actor, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    object  enemy,
            effect_obj;
    string  taunt,
            message,
            player_msg,
            enemy_msg,
            watcher_msg;
    int     task;
    
    enemy   = target;
        
    if (result > 0)
    {
        actor->catch_msg("You find an opening in your opponents' "
        +"defenses and quickly step in with a strong kick to the "
        +"forehead!\n");

        enemy->catch_msg(QCTNAME(actor)+" finds an opening in "
        +"your defenses and quickly steps in with a strong kick to "
        +"your forehead!\n");

        actor->tell_watcher(QCTNAME(actor)+" finds an opening in "
        +QTNAME(enemy)+"'s defenses and quickly steps in with a "
        +"strong kick to the forehead!\n",enemy, ({ actor, enemy }));

        setuid();
        seteuid(getuid());
            
        effect_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/stun_obj");
        
        effect_obj->move(enemy);
        effect_obj->start();
		
		// Temporary solution to cooldown obj
        object stun_cooldown_obj;
       
        stun_cooldown_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/stun_cooldwn_obj");
        
        stun_cooldown_obj->set_bestower(actor->query_name());
        stun_cooldown_obj->move(actor, 1);
    }
    else
    {
        actor->catch_msg("You find an opening in your opponents' "
        +"defenses and try to step in with a strong kick to the forehead "
        +"but "+QTNAME(enemy)+" blocks it just in time.\n");

        enemy->catch_msg(QCTNAME(actor)+" finds an opening in your "
        +"defenses and tries to step in with a strong kick to the "
        +"forehead but you manage to block it just in time.\n");
        
        actor->tell_watcher(QTNAME(actor)+" finds an opening in "
        +QTNAME(enemy)+"'s defenses and tries to step in with a strong "
        +"kick to the forehead but "+QTNAME(enemy)+" manages to block "
        +"it just in time.\n", enemy, ({ actor, enemy }));
		
		object stun_cooldown_obj2;
       
        stun_cooldown_obj2 = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/stun_cooldwn_obj");
        
        stun_cooldown_obj2->set_bestower(actor->query_name());
        stun_cooldown_obj2->move(actor, 1);
    }
}


public void
hook_special_complete()
{
	object token;
    
	if (token = present("_stun_cooldwn_obj", this_player()))
	{   		
		token->remove_object();
	}
	
    write("You feel ready to execute stun or any "
    +"other primary ability again.\n");
}


public void
hook_already_active(object ability)
{
    write("You are already preparing to stun someone!\n");
}


public void
hook_special_in_cooldown()
{
    write("You're not ready to stun someone yet.\n");
}


