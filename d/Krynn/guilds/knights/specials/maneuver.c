/*
 * /d/Krynn/guilds/knights/specials/maneuver.c
 *
 * Knights who are mounted on a warhorse need a way to protect their mounts
 * from attack. The maneuver ability is very similar to the rescue ability
 * except that a Knight does it with his mount.
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

public void config_ability()
{
    ::config_ability();
    set_ability_name("maneuver");
    set_ability_offensive(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(60);
    set_ability_target(target_actor);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("Seeing your steed under attack, you focus on "
        + "a way to maneuver your steed to draw your enemy's "
        + "attention again...\n");
}

static mixed * 
check_required_items(object actor,mixed * targets,
                     string arg,int pretest)
{
    object horse;
    
    // The horse can be any mounted steed
    horse = actor->query_prop(LIVE_O_STEED);
    
    return ({ horse });
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    int lev, skill, duration;
    object steed, maneuver_obj;
    object * enemies;
    
    lev = actor->query_knight_level();
    if (lev > L_CROWN)
        lev = 10;
    else if (lev == L_CROWN)
        lev = actor->query_knight_sublevel();
    else
        lev = (actor->query_knight_sublevel() / 2);

    skill = ((actor->query_stat(SS_INT) + (lev * 2) +
        actor->query_skill(SS_MOUNTED_COMBAT)) / 2);

    if (skill > 100)
        skill = 100;

    steed = items[0];
    enemies = filter(all_inventory(environment(actor)),
	    &operator(==)(steed) @ &->query_attack());	    
    if ((skill - (sizeof(enemies) * 25)) <= 0)
    {
        actor->catch_tell("You fail to maneuver your steed safely out "+
          "of harm's way.\n");
        return;
    }

    actor->catch_tell("Recalling your training of mounted combat, you "+
      "spur your " + steed->steed_short() + " forward and whirl " +
      POSSESSIVE(steed) + " around to face " + POSSESSIVE(steed) +
      " assailents.\n");
    tell_room(E(actor), QCTNAME(actor) + " spurs " + POSSESSIVE(actor) + " " +
      steed->steed_short() + " forward and whirls around, facing " +
      POSSESSIVE(actor) + " assailants head on.\n", enemies + ({ actor }));

    foreach (object enemy : enemies)
    {
        enemy->stop_fight(steed);
        steed->stop_fight(enemy);
        enemy->attack_object(actor);
        enemy->catch_msg(QCTNAME(actor) +
          " spurs " + POSSESSIVE(actor) + " " + steed->steed_short() +
          " forward and whirls around, facing you head on.\n");
    }

    if (!steed->has_knight_maneuver_shadow())
    {
        setuid();
        seteuid(getuid());
    
        maneuver_obj = clone_object(SPECIALS + "objects/maneuver_shadow");
        maneuver_obj->shadow_me(steed);
        duration = (skill - (sizeof(enemies) * 20) + 20);
        steed->set_maneuver_duration(duration);
    }
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
}

public void
hook_special_in_cooldown()
{
    write("You are not yet ready to maneuver your steed again.\n");
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
    object steed;
    object * attackers;
    
    steed = player->query_prop(LIVE_O_STEED);
    if (!objectp(steed))
    {
        player->catch_msg("You need a mount first!\n");
        return 0;
    }
    
    attackers = filter(all_inventory(environment(player)),
	    &operator(==)(steed) @ &->query_attack());
    
    if (!sizeof(attackers))
    {
        player->catch_msg("Your " + steed->steed_short() + " is not under "
            + "attack, there is no need.\n");
        return 0;
    }
    
    if (sizeof(attackers) >= 4)
    {
        player->catch_msg("The onslaught is too overwhelming, you "+
          "cannot possibly save your steed from so many attackers "+
          "at once.\n");
        return 0;
    }
    
    if (objectp(present("_knight_maneuver_object_", steed)))
    {
        player->catch_msg("You are already carefully guarding your steed "
            + "from attacks.\n");
        return 0;
    }
    
    return 1;
}
