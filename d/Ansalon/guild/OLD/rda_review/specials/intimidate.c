/*
 * Dragonarmy Dishearten Ability
 *
 * This ability is similar to dragonfear in that it applies penalties
 * to an opponent's defence. It can be used only indoors where a DA
 * member cannot summon a dragon.
 *
 * Modifications:
 *   - Renamed from Intimidate to Dishearten to match descriptions
 *     more closely.
 *          Petros, April 2009
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include "defs.h"

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

#include "/std/combat/combat.h"

// Prototypes
public void             config_ability();
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);

// Defines
#define INTIMIDATE_OBJ  (DRAGONARMY_SPECIALS + "intimidate_obj")
#ifndef LIVE_I_NO_DRAGONFEAR
#define LIVE_I_NO_DRAGONFEAR "_live_i_no_dragonfear"
#endif

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

    set_ability_name("dishearten");
    set_ability_offensive(1);
    set_ability_stationary(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(5);
    set_ability_target(target_one_other_present_living_or_enemy);
}


static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You gather yourself and prepare to dishearten "
        + QTNAME(targets[0]) + ".\n");
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object enemy;
    string player_msg, enemy_msg, watcher_msg;
    
    enemy = targets[0];
    player_msg = "You forcefully shout at " + QTNAME(enemy)
        + " and invoke the wrath of the Dark Queen upon "
        + enemy->query_objective() + ". " ;
    enemy_msg = QCTNAME(actor) + " forcefully shouts curses "
        + "at you and invokes the wrath of the Dark Queen Takhisis. ";
    watcher_msg = QCTNAME(actor) + " forcefully "
        + "shouts curses at " + QTNAME(enemy) + " and invokes the "
        + "wrath of the Dark Queen Takhisis. ";
    if (actor->resolve_task(TASK_EASY,
                            ({ TS_STR, TS_DIS }),
                            enemy,
                            ({ TS_DIS, SS_AWARENESS })) > 0)
    {
        setuid();
        seteuid(getuid());
        clone_object(INTIMIDATE_OBJ)->move(enemy, 1);
        player_msg += capitalize(enemy->query_pronoun())
            + " looks visibly shaken.\n";
        enemy_msg += "You are shaken and filled with a sense of "
            + "impending doom.\n";
        watcher_msg += capitalize(enemy->query_pronoun()) + " looks visibly "
            + "shaken.\n";
    }
    else
    {
        player_msg += capitalize(enemy->query_pronoun()) + " looks at you "
            + "and ignores your efforts.\n";
        enemy_msg += "You are not affected by such vain attempts to "
            + "dishearten you.\n";
        watcher_msg += capitalize(enemy->query_pronoun()) + " looks at "
            + actor->query_objective() + " and does not seem affected.\n";
    }
    
    actor->catch_msg(player_msg);
    enemy->catch_msg(enemy_msg);
    actor->tell_watcher(watcher_msg, enemy, ({ actor, enemy }));
}

public void
hook_special_complete()
{
    write("You feel ready to dishearten someone again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are already trying to invoke the wrath of your Dark "
        + "Queen!\n");
}

public void
hook_special_in_cooldown()
{
    write("You cannot dishearten someone again so soon.\n");
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
    
    enemy = targets[0];    
    if(!IS_MEMBER(player) || player->query_dragonarmy_promotions() < 2)
    {
    	player->catch_tell("You have no idea how to do that!\n");
    	return 0;
    }

    if(!E(player)->query_prop(ROOM_I_INSIDE))
    {
        player->catch_tell("Why not just summon a dragon?\n");
        return 0;
    }

    if (enemy->has_intimidate_shadow())
    {
        player->catch_msg(QCTNAME(enemy) + " already looks disheartened!\n");
        return 0;
    }
    
    if (enemy->query_dragonarmy_promotions() > 1
        || (enemy->query_pot_member() && enemy->query_priest_level() > 0)
        || QRACE(enemy) == "draconian"
        || QRACE(enemy) == "dragon"
        || enemy->query_dragonfear_immunity()
        || enemy->query_wiz_level()
        || enemy->query_prop(LIVE_I_NO_DRAGONFEAR))
    {
        player->catch_msg("You doubt that "
            + QTNAME(enemy) + " would be affected by your efforts.\n");
        return 0;        
    }
    
    return ::check_valid_action(player, targets, arg, execute);
}
