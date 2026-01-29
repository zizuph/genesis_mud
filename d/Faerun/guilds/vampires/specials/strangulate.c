/*
 * Strangulate combat special for Vampires
 *
 * Nerull 2021
 *
 */

#pragma strict_types

inherit "/d/Genesis/specials/timed_ability";
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
    set_ability_name("strangulate");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(3);
    set_ability_cooldown_time(107);
    set_ability_offensive(1);
    set_ability_target(target_one_other_present_living_or_enemy);
    
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/bloodletter.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/trucidate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/execute.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/mesmerize.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/ethereal.c");
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
    
    object silence_token;
    
    enemy = targets[0];
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(player->query_name()) != 2 
    && VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(player->query_name()) != 3)
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
        player->catch_tell("The dead cannot be silenced by this method!\n");

        return 0;
    }
    
    if (present("_strangulate_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent strangulation of the "
        +"target, strangulate is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (present("_mesmerize_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent mesmerize of the "
        +"target, strangulate is not yet ready to be used! Patience!\n");

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
    actor->catch_msg("You prepare to strangle your opponent with your hands.\n");
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
    
    if (result > 0)
    {
        actor->catch_msg("With savage ferocity you surge forward "
        +"and sieze "+enemy->query_possessive()+" throat "
        +"in a powerful, crushing grip, closing "
        +"off "+enemy->query_objective()+" windpipe.\n");

        enemy->catch_msg(QCTNAME(actor)+ " savagely rushes "
        +"forward and siezes your throat in a crushing grip.  "
        +"As "+actor->query_possessive()+" hand squeezes "
        +"tighter and tighter, stars burst in your vision and "
        +"you feel as though you are going to pass out.\n");

        actor->tell_watcher(QCTNAME(actor) +" ferociously "
        +"siezes "+QTNAME(enemy)+" by the throat. As the "
        +"tension continues to increase around "+enemy->query_possessive()+"'s "
        +"neck, bulging eyes reveal the flaccid signs of asphyxiation.\n", 
        enemy, ({ actor, enemy }));

        setuid();
        seteuid(getuid());
            
        effect_obj = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/strangulate_obj");
        
        effect_obj->move(enemy);
        effect_obj->start();
        
        object strangulate_cooldown_obj;
       
        strangulate_cooldown_obj = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/strangulate_cooldwn_obj");
        
        strangulate_cooldown_obj->set_bestower(actor->query_name());
        strangulate_cooldown_obj->move(actor, 1);
    }
    else
    {
        actor->catch_msg("You hastily attempt to grasp "+QTNAME(enemy)+" by "
        +"the throat but find yourself thwarted by a deft parry.\n");

        enemy->catch_msg("You see "+QCTNAME(actor)+" attempting "
        +"to snatch you by the throat but deftly parry the "
        +"grab.\n");

        actor->tell_watcher(QTNAME(actor)+" lunges forward in an "
        +"attempt to sieze "+QTNAME(enemy)+" by the throat, but "
        +"is deftly thwarted.\n", 
        enemy, ({ actor, enemy }));
        
        object strangulate_cooldown_obj2;
       
        strangulate_cooldown_obj2 = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/strangulate_cooldwn_obj");
        
        strangulate_cooldown_obj2->set_bestower(actor->query_name());
        strangulate_cooldown_obj2->move(actor, 1);
    }
}


public void
hook_special_complete()
{
    object token;
    
    if (token = present("_strangulate_cooldwn_obj", this_player()))
    {           
        token->remove_object();
    }
    
    write("You feel ready to stranguilate or use any other ability again.\n");
}


public void
hook_already_active(object ability)
{
    write("You are already preparing to strangulate someone!\n");
}


public void
hook_special_in_cooldown()
{
    write("You're not ready to strangulate someone yet.\n");
}


