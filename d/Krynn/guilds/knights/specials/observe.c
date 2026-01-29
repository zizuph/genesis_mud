/*
 * /d/Krynn/guilds/knights/specials/observe.c
 *
 * This is the observe ability for Knights. It allows them to observe a
 * team carefully and determine who is the leader of the team. this is
 * especially useful in combat tactics as eliminating the leader
 * often times throws the rest of the party into disarray
 *
 * Notes from a previous implementation:
 * Ability for Level 6 Crown Knights and up (Including Rose and Sword)
 * The command lets them observe another object and allows them to
 * observe who that object's leader is with a percentage chance based
 * on appraise enemy skill and wisdom stat. It has a 10 second resetting
 * time to prevent the Knight from using it multiple times to negate the
 * chance for error.
 *
 * Created by Petros, October 2008
 */
 
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public object * target_present_living_observe(object actor, string str);

public void config_ability()
{
    ::config_ability();
    set_ability_name("observe");
    set_ability_offensive(0);
    set_ability_hasted(0); // no haste changes to berserk
    set_ability_prep_time(0);
    set_ability_cooldown_time(10);
    set_ability_target(target_present_living_observe);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    object target, leader;
    string pos, pro;
    int percentage, appskill, chance;
    
    if (pointerp(targets) && sizeof(targets) > 0 && objectp(targets[0]))
    {
        target = targets[0];
    }
    
    if (!objectp(target))
    {
        return;
    }
    
    percentage = random(100) + 1;

    if (target->query_team_others())
    {
        leader = target->query_leader();
    }
    
    if (sizeof(target->query_team()) > 0)
    {
        leader = target;
    }
    
    pos = target->query_possessive();
    pro = target->query_pronoun();
    
    appskill = actor->query_skill(SS_APPR_MON);
    if (appskill > 50)
        appskill = 50;
    
    chance = appskill + actor->query_stat(SS_WIS) / 2;
    if (chance > 99)
        chance = 99;
    
    if (chance < percentage || !objectp(leader)
        || !present(leader, environment(actor)))
    {
        actor->catch_msg("You observe " + QTNAME(target) + " carefully, "
            + "but see no sign of a leader present.\n");
    }
    else if (leader == target)
    {
        actor->catch_msg("You observe " + QTNAME(target) + " carefully "
            + "and realize that " + pro + " is the leader.\n");
    }
    else if (leader == actor)
    {
        actor->catch_msg("You feel stupid as you realize that " 
            + QTNAME(target) + " is on YOUR team.\n");
    }
    else
    {
        actor->catch_msg("You observe " + QTNAME(target) + " carefully "
            + "and realize that " + QTNAME(leader) + " is " + pos
            + " leader.\n");
    }
    
    target->catch_msg(QCTNAME(actor) + " observes you carefully.\n");
    tell_room(environment(actor), QCTNAME(actor) + " observes "
        + QTNAME(target) + " carefully.\n", ({ actor, target }), actor);
}

public void
hook_special_complete()
{
   write("Your mind feels clear and observant again.\n");    
}

public void
hook_already_active(object ability)
{
}

public void
hook_special_in_cooldown()
{
    write("Your mind is still strained from observing before.\n");    
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
    if (!targets || !sizeof(targets))
    {
        player->catch_tell("Observe whom?\n");
        return 0;
    }

    if (sizeof(targets) > 1)
    {
        write("You can only consider one individual at a time.\n");
        return 0;
    }

    if (player->query_knight_level() == L_SQUIRE 
        || (player->query_knight_level() == L_CROWN 
            && player->query_knight_sublevel() < L_6 ))
    {
        player->catch_tell("You are not yet experienced enough in battle "
            + "to be able to observe someone.\n");
        return 0;
    }
    
    if (player->query_stat(SS_WIS) < 50)
    {
        player->catch_tell("You lack the wisdom to be able to observe "
            + "someone properly.\n");
        return 0;
    }
    
    if (player->query_skill(SS_APPR_MON) < 25)
    {
        player->catch_tell("You lack the knowledge of military tactics "
            + "necessary to properly observe someone.\n");
        return 0;
    }
       
    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: target_observe
 * Description  : Targeting function used for the observe ability
 * Arguments    : actor - person doing the observing
 *                str   - the string argument passed in
 * Returns      : Object array of matching targets
 */
public object *
target_present_living_observe(object actor, string str)
{
    object * oblist;

    if (!strlen(str))
    {
        actor->catch_tell("Whom do you wish to observe?\n");
        return ({ });
    }
    
    return target_one_present_living(actor, str);
}
