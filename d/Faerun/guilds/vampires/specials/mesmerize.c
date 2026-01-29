/*
 * Mesmerize combat special for the Vampires
 *
 * Nerull 2021
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
    set_ability_name("mesmerize");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(3);
    set_ability_cooldown_time(57);
    set_ability_offensive(1);
    set_ability_target(target_one_other_present_living_or_enemy);
    
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/bloodletter.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/trucidate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/execute.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/ethereal.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/strangulate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/vampfly.c");
}


string
query_component()
{
    return "";
}


public int
check_valid_action(object player, mixed * targets, string arg, 
int execute = 0)
{
    object enemy;
    object * enemies;
    
    object stun_token;
    
    enemy = targets[0];
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(player->query_name()) == 0)
    {
        write("What?\n");
        return 0;
    }
    
    if (!present("_vampire_powers_unlock_ob", player))
    {
        player->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(player->query_real_name());
    
    if (check < ABILITY_THRESHOLD)
    {
        player->catch_tell("You are too weak. Aquire more blood!\n");
        
        return 0;
    }
    
    if (player->query_ethereal() == 1)
    {
        player->catch_tell("You are in the ethereal realm. This ability "
        +"doesn't work there.\n");
        
        return 0;
    }
    
    if (enemy->query_prop(LIVE_I_UNDEAD))
    {
        player->catch_tell("The dead cannot be mesmerized.\n");

        return 0;
    }
    
    if (present("_strangulate_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent mesmerize of the "
        +"target, mesmerize is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (present("_mesmerize_cooldwn_obj", player))
    {
        player->catch_tell("Mesmerizing victims is a taxing "
        +"practice, requiring less exertion for a  period of "
        +"time while you gather yourself.\n");

        return 0;
    }
    
    if (STRANGULATE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to strangulate!\n");
        return 0;
    }
    
    if (MESMERIZE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to mesmerize!\n");
        return 0;
    }
    
    if (EXECUTE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to execute!\n");
        return 0;
    }
    
    if (BLOODLETTER_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to bloodletter!\n");
        return 0;
    }
    
    if (TRUCIDATE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to trudicate!\n");
        return 0;
    }
     
    return 1;
}


static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You prepare to mesmerize your target.\n");
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
        actor->catch_msg("You stare hauntingly at "+QTNAME(enemy)+" attempting "
        +"to immobilize "+enemy->query_objective()+" with "
        +"your hypnotic gaze.\n");

        enemy->catch_msg(QCTNAME(actor)+" stares at you with a "
        +"hypnotic gaze. You feel your limbs becoming slack "
        +"and unresponsive as you gaze back into those "
        +"hollow, haunting eyes.\n");

        actor->tell_watcher(QTNAME(enemy)+" becomes as limp as "
        +"a boned fish as "+QCTNAME(actor)+" gazes hypnotically "
        +"at "+enemy->query_objective()+"\n",enemy, ({ actor, enemy }));

        setuid();
        seteuid(getuid());
            
        effect_obj = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/mesmerize_obj");
        
        effect_obj->move(enemy);
        effect_obj->start();
        
        // Temporary solution to cooldown obj
        object stun_cooldown_obj;
       
        stun_cooldown_obj = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/mesmerize_cooldwn_obj");
        
        stun_cooldown_obj->set_bestower(actor->query_name());
        stun_cooldown_obj->move(actor, 1);
    }
    else
    {
        actor->catch_msg("You attempt to mesmerize your prey with "
        +"a hypnotic stare, but "+QTNAME(enemy)+" seems to "
        +"be very resilient.\n");

        enemy->catch_msg("You feel very strange as "+QCTNAME(actor)+" stares "
        +"hauntingly at you. You manage to fight the sensation and snap "
        +"back to reality, fully focused.\n");

        actor->tell_watcher(QCTNAME(actor)+" gazes hypnotically "
        +"at "+QTNAME(enemy)+" but the gaze seems to have only "
        +"the most brief of effects.\n", enemy, ({ actor, enemy }));
        
        object stun_cooldown_obj2;
       
        stun_cooldown_obj2 = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/mesmerize_cooldwn_obj");
        
        stun_cooldown_obj2->set_bestower(actor->query_name());
        stun_cooldown_obj2->move(actor, 1);
    }
}


public void
hook_special_complete()
{
    object token;
    
    if (token = present("_mesmerize_cooldwn_obj", this_player()))
    {           
        token->remove_object();
    }
    
    write("You feel ready to mesmerize or any "
    +"other ability again.\n");
}


public void
hook_already_active(object ability)
{
    write("You are already preparing to mesmerize someone!\n");
}


public void
hook_special_in_cooldown()
{
    write("You're not ready to mesmerize someone yet.\n");
}


