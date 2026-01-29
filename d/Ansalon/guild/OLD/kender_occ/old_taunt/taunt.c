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

#include "guild.h"

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
    set_ability_name("taunt");
    set_ability_attack_during_prep(1);
    set_ability_stationary(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(30);
    set_ability_target(target_one_other_present_living_or_enemy);
}

static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You rack your brain for an appropriate taunt.\n");
}

static void 
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *results)
{
    object  enemy,
            shadow;
    string  taunt,
            message,
            player_msg,
            enemy_msg,
            watcher_msg;
    int     task;
    
    enemy   = targets[0];
    task    = actor->resolve_task(TASK_ROUTINE, 
              ({ SKILL_AVG, TS_OCC, TS_WIS, SKILL_END, SS_TAUNT_SPECIAL }),
              enemy, ({ SKILL_AVG, TS_DIS, TS_INT, SKILL_END }));
    
    task = min(task, 100) / 3;
    
    taunt   = TAUNT_LIST->query_all_taunt(enemy);
    
    if ((enemy->query_stat(SS_INT) < 10 && enemy->query_humanoid()) ||
        (enemy->query_stat(SS_INT) < 20 && !enemy->query_humanoid()))
    {
        actor->catch_msg("\n" + enemy->query_The_name(actor) +
        " looks dumbly at you as you yell out: " + taunt + " " +
        capitalize(enemy->query_pronoun()) + " is obviously too " +
        "dumb to understand what you are saying.\n\n");
        
        enemy->catch_msg(actor->query_The_name(enemy) + " yells " +
        "something at you, but it seems just nonsense words.\n");
        
        tell_room(environment(actor), "\n" + QCTNAME(enemy) +
        " looks dumbly at " + QTNAME(actor) + " as " +
        actor->query_pronoun() + " yells out: " + taunt + "\n\n",
        ({ actor, enemy }));
        
        return;
    }
    
    if (task > 0)
    {
        switch(task)
        {
            case 1..5:
            message = "cheeks flush slightly in annoyance";
                break;
                
            case 6..10:
            message = "cheeks flush in annoyance";
                break;
                
            case 11..15:
            message = "face flushes in anger";
                break;
                
            case 16..20:
            message = "face flushes darkly in anger";
                break;
                
            case 21..25:
            message = "face flushes in rage";
                break;
                
            case 26..30:
            message = "face flushes hotly in rage";
                break;
                
            default:
            message = "face flushes in complete rage";
                break;
        }
        
        actor->catch_msg("\n" + QCTPNAME(enemy) + " " + message + " as " +
            QTNAME(actor) + " taunts " + enemy->query_objective() +
            ", yelling: " + taunt + "\n\n");
        
        enemy->catch_msg("\nYour " + message + " as you listen to " +
            actor->query_the_name(enemy) + " taunting you, yelling: " +
            taunt + "\n\n");
            
        actor->tell_watcher("\n" + QCTPNAME(enemy) + " " + message + " as " +
            QTNAME(actor) + " taunts " + enemy->query_objective() + "\n\n",
            enemy, ({ actor, enemy }));
        
        if (!enemy->query_kender_rage())
        {
            setuid();
            seteuid(getuid());
            shadow = clone_object(TAUNT_SH);
            shadow->shadow_me(enemy);
            shadow->init_rage_decay();
        }
        
        enemy->add_kender_rage(task, actor);
    }
    else
    {
        actor->catch_msg("\n" + enemy->query_The_name(actor) + " retains " +
            enemy->query_possessive() + " calm composure as you " +
            "yell a taunt at " + enemy->query_objective() + ".\n\n");
            
        enemy->catch_msg("\nYou retain your calm composure as " +
            actor->query_the_name(enemy) + " attempts to taunt " +
            "you.\n\n");
            
        actor->tell_watcher("\n" + QCTNAME(enemy) + " retains " +
            enemy->query_possessive() + " calm composure as " + 
            QTNAME(actor) + " attempts to taunt " + 
            enemy->query_objective() + ".\n\n", enemy, ({ actor, enemy }));
    }
}

public void
hook_special_complete()
{
    write("You feel ready to think of a brilliant new taunt!\n");
}

public void
hook_already_active(object ability)
{
    write("You are already composing a taunt.\n");
}

public void
hook_special_in_cooldown()
{
    write("You're not ready to compose a new taunt yet.\n");
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
check_valid_action(object player, mixed *targets, string arg, int execute)
{
    if (player->query_skill(SS_TAUNT_SPECIAL) < 1)
    {
        write("You don't have enough skill to taunt anyone.\n");
        return 0;
    }

    /* Temporary Solution*/
    if ("/d/Ansalon/guild/society/wimpy_check.c"->wimp_check(player) < player->query_whimpy())
    {
        write("You are too busy thinking about running away to " +
        "compose a taunt.\n");
        return 0;
    }
    return 1;
}