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
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/d/Faerun/guilds/halflings/halflings.h"

#include "/std/combat/combat.h"

#define COOLDOWN        86400
#define BLIND_TIME      6
#ifndef HALFLING
#define HALFLING_BLIND  (HALFGLD_DIR + "halfling_blind.c")
#define HALFLING(who)   (GUILD_DATA + who)
#endif

// Prototypes
public void             config_ability();
static int              check_valid_action(object player, mixed *targets, 
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
    set_ability_name("hhurl");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(1);
    set_ability_target(target_one_other_present_living_or_enemy);
}


static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You prepare to throw a pie.\n");
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object  enemy,
            blind;
    
    string  player_msg,
            enemy_msg,
            watcher_msg;
    mapping halfling;

    halfling    = restore_map(HALFLING(actor->query_real_name()));
    enemy       = targets[0];
    
    player_msg  = "You throw a pie at " + QTNAME(enemy) + ", " ;
    enemy_msg   = QCTNAME(actor) + " throws a pie at you, ";
    watcher_msg = QCTNAME(actor) + " throws a pie at " +
    QTNAME(enemy) + ", ";
    
    if (actor->resolve_task(TASK_EASY, ({ TS_DEX, TS_DIS }),
                            enemy, ({ TS_DEX, SS_AWARENESS })) > 0)
    {
        setuid();
        seteuid(getuid());
        /* Clone blind */
        blind = clone_object(HALFLING_BLIND);
        blind->set_time(BLIND_TIME);
        blind->move(enemy);
        
        player_msg  += capitalize(enemy->query_pronoun()) +
        " is blinded by the pie.\n";
        enemy_msg   += "the pie hits you in the face, blinding you.\n";
        watcher_msg += capitalize(enemy->query_pronoun()) + " is " +
        "hit in the face and blinded by the pie.\n";
        
        halfling["Last_Hurl"] = time();
        
        save_map(halfling, HALFLING(actor->query_real_name()));
    }
    else
    {
        player_msg  += "missing by a mile.\n";
        enemy_msg   += "but misses by a mile.\n";
        watcher_msg += "but misses by a mile.\n";
    }
    
    actor->catch_msg(player_msg);
    enemy->catch_msg(enemy_msg);
    actor->tell_watcher(watcher_msg, enemy, ({ actor, enemy }));
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already taking aim!\n");
}

public void
hook_special_in_cooldown()
{
    write("Throwing a pie again? You must be crazy, this is getting expensive.\n");
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
    mapping halfling;
    
    setuid();
    seteuid(getuid());
    
    if (file_size(GUILD_DATA + player->query_real_name() + ".o") < 0)
        save_map((["Last_Hurl" : 0]), HALFLING(player->query_real_name()));
    
    halfling = restore_map(HALFLING(player->query_real_name()));
    
    if (time() - halfling["Last_Hurl"] < COOLDOWN)
    {
        hook_special_in_cooldown();
        return 0;
    }
    
    return ::check_valid_action(player, targets, arg, execute);
}