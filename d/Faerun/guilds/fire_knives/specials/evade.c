
/*
 * Evade special for the Fire Knives.
 * 
 */
 
#pragma strict_types

inherit "/d/Genesis/specials/timed_ability";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include <math.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"

#include "../guild.h"

public void config_ability()
{
    ::config_ability();
    set_ability_name("evade");
    set_ability_hasted(0);
    set_ability_offensive(0);
    set_ability_prep_time(30);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);
}


public void
remove_fireknives_evade(object actor)
{
    object *evades;

    if (!actor->has_evade_shadow())
    {
        return;
    }

    // Remove all existing evades first
    evades = actor->query_evade_effects() + all_inventory(actor);
    evades = filter(evades, &->is_fireknives_evade());
    
    if (sizeof(evades))
    {
        evades->remove_object();
    }
}


static void
ability_msg(object actor, mixed *targets, string arg)
{
    object evade_obj;
    
    setuid();
    seteuid(getuid());
    
    write("Your eyes narrow as you turn your full "
    +"focus on evading any assaults directed at you.\n");
    
    // Remove all existing evades first
    remove_fireknives_evade(actor);
    
    evade_obj = clone_object(FIREKNIVES_GUILD_DIR 
    + "specials/obj/evade_obj.c");
    
    evade_obj->set_effect_caster(actor);
    evade_obj->set_effect_target(actor);
    evade_obj->move(actor, 1);
    evade_obj->start();
}


static void
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *results)
{
    remove_fireknives_evade(actor);    
}


public void
hook_special_complete()
{
    write("You feel ready to execute evade or "
    +"any other primary ability again.\n");    
}


public void
hook_already_active(object ability)
{
    write("You are already evading!\n");
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
    
    enemy = player->query_attack();

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (FIREKNIVES_MAPPINGS->query_ability2(player->query_name()) == 0)
    {
        player->catch_tell("What?\n");
        
        return 0;
    }

    if (!player->query_skill(SS_ART))
    {
        player->catch_tell("You are not skilled the Arts of Assassination!\n");

        return 0;
    }
    
    /*if (player->query_enemy() == 0)
    {
        player->catch_tell("No present enemy to evade here!\n");
        
        return 0;
    } */
   
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
 
    /*if (objectp(blind_token = present("_blind_cooldwn_obj", enemy)))
    {
        // If we bestowed blind on the target, then we stop this special
        if (blind_token->query_bestower() == player->query_name())
        {
            player->catch_tell("Due to your recent blinding of the "
            +"target, evade is not yet ready to be used! Patience!\n");

            return 0;
        }
    }
    
    if (objectp(silence_token = present("_silence_cooldwn_obj", enemy)))
    {
        // If we bestowed silence on the target, then we stop this special
        if (silence_token->query_bestower() == player->query_name())
        {
            player->catch_tell("Due to your recent garotte of the "
            +"target, evade is not yet ready to be used! Patience!\n");

            return 0;
        }
    }
	
	if (objectp(stun_token = present("_stun_cooldwn_obj", enemy)))
    {
        // If we bestowed silence on the target, then we stop this special
        if (stun_token->query_bestower() == player->query_name())
        {
            player->catch_tell("Due to your recent stun of the "
            +"target, garotte is not yet ready to be used! Patience!\n");

            return 0;
        }
    }*/
       
    if (present("_blind_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent blinding of the "
        +"target, evade is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garotte of the "
        +"target, evade is not yet ready to be used! Patience!\n");

        return 0;
    }
	
	if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, evade is not yet ready to be used! Patience!\n");

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

    // If it passes everything, return success
    return 1; 
}