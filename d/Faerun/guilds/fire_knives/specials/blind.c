/*
 * Blind combat special for the Fire Knives
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
    set_ability_name("blind");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(109);
    set_ability_offensive(1);
    set_ability_target(target_one_other_present_living_or_enemy);
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
    
    if (FIREKNIVES_MAPPINGS->query_ability3(player->query_name()) == 0)
    {
        player->catch_tell("What?\n");
        
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


static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You prepare to blind your target.\n");
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
    int     task;
    
    enemy   = target;
    
    // Blind component
    obb = filter(deep_inventory(actor),
    &operator(==)(query_component()) @&->query_name());

    // This should never happen
    if (!sizeof(obb))
    {
        actor->catch_msg("Too late you realize you are out of blinding powder!\n");
        
        return;
    } 

    obb[0]->reduce_heap_size();       
    
    if (result > 0)
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
        
       
        setuid();
        seteuid(getuid());
            
        effect_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/blind_obj");
        
        effect_obj->move(enemy);
        effect_obj->start();
        
        object blind_cooldown_obj;
       
        blind_cooldown_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/blind_cooldwn_obj");
        
        blind_cooldown_obj->set_bestower(actor->query_name());
        blind_cooldown_obj->move(actor, 1);
    }
    else
    {
        actor->catch_msg("You take out a small pinch of red "
        +"powder from your belongings "
        +"and try to blow it on "
        +QTPNAME(enemy)+" eyes, but "
        +"you miss.\n");
            
        enemy->catch_msg(QCTNAME(actor)+" takes out a small pinch of "
        +"red powder from "+actor->query_possessive()+" belongings and "
        +"attempts to blow it on "+QTPNAME(enemy)+" eyes but misses.\n");
            
        actor->tell_watcher(QTNAME(actor)+" takes out a small pinch of red powder "
        +"from "+actor->query_possessive()+" belongings and attempts "
        +"to blow it on your "
        +"eyes, but misses.\n", enemy, ({ actor, enemy }));
		
		object blind_cooldown_obj2;
       
        blind_cooldown_obj2 = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/obj/blind_cooldwn_obj");
        
        blind_cooldown_obj2->set_bestower(actor->query_name());
        blind_cooldown_obj2->move(actor, 1);
    }
}


public void
hook_special_complete()
{
	object token;
    
	if (token = present("_blind_cooldwn_obj", this_player()))
	{   		
		token->remove_object();
	}
	
    write("You feel ready to execute blind or any other primary ability again.\n");
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


