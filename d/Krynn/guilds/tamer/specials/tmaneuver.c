#pragma strict_types

#include "defs.h"

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

// Global Variables
static mapping  gManeuver = ([]);

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public
void config_ability()
{
    ::config_ability();
    set_ability_name("tmaneuver");
    set_ability_hasted(0);
    set_ability_offensive(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(15);
    set_ability_target(target_present_enemies);
} /* config_ability */

/*
 * Function name: ability_msg
 * Description:   Displays the ability message.
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    object mount = MANAGER->query_current_pet(actor);
    
    if (gManeuver[actor] != "advance")
        actor->catch_msg("Seeing your pet under attack, you look for an "
        + "opportunity to draw the attention away from "
        + (objectp(mount) ? mount->query_objective() : "it") + ".\n");
    else
        actor->catch_msg("You send " + (objectp(mount) ? QTNAME(mount) : "your "
        + "pet") + " forward to draw the attention away from you.\n");
} /* ability_msg */

static mixed * 
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    object mount;
    
    if (objectp(mount = MANAGER->query_current_pet(actor)))
        return ({ mount });
    
    return ({});
}

public void
hook_maneuver_success(object protector, object protected, object *enemies)
{
    if (interactive(protector))
    {
        if (protector->query_steed() == protected)
        {
            protector->catch_msg("You maneuver " + QTNAME(protected) + " "
            + "out of harms way and whirl " + protected->query_objective()
            + " around to face " + COMPOSITE_LIVE(enemies) + " head on.\n");
            enemies->catch_msg(QCTNAME(protector) + " maneuvers "
            + QTNAME(protected) + " out of harms way and whirls around "
            + "to face you head on.\n");
            tell_room(environment(protector), QCTNAME(protector)
            + " maneuvers " + QTNAME(protected) + " out of harms way and "
            + "whirls around, facing " + COMPOSITE_LIVE(enemies) + " head "
            + "on.\n", enemies + ({ protected, protector }), protector);
            return;
        }
        
        protector->catch_msg("You command " + QTNAME(protected) + " to "
        + "retreat to your side and protect " + protected->query_objective()
        + " from " + COMPOSITE_LIVE(enemies) + ".\n");
        enemies->catch_msg(QCTNAME(protector) + " commands " + QTNAME(protected)
        + " to retreat to " + protector->query_possessive() + " side and "
        + "protects " + protected->query_objective() + " from your assault.\n");
        tell_room(environment(protector), QCTNAME(protector) + " commands "
        + QTNAME(protected) + " to retreat to " + protector->query_possessive()
        + " side and protects " + protected->query_objective() + " from "
        + COMPOSITE_LIVE(protected) + ".\n", enemies
        + ({ protector, protected }), protector);
        return;
    }
    
    protected->catch_msg(QCTNAME(protector) + " intercepts "
    + COMPOSITE_LIVE(enemies) + ", forcing " + (sizeof(enemies) > 1 ? "them" :
    enemies[0]->query_objective()) + " to attack "
    + protector->query_objective() + " instead.\n");
    enemies->catch_msg(QCTNAME(protector) + " intervenes in your attempt to "
    + "attack " + QTNAME(protected) + ", forcing you to attack "
    + protector->query_objective() + " instead.\n");
    tell_room(environment(protector), QCTNAME(protector) + " intercepts "
    + COMPOSITE_LIVE(enemies) + ", forcing " + (sizeof(enemies) > 1 ? "them" :
    enemies[0]->query_objective()) + " to attack "
    + protector->query_objective() + " instead.\n", enemies + ({ protector,
    protected }), protector);
}

public void
hook_maneuver_failed(object protector, object protected, object *targets)
{
    targets->catch_msg(QCTNAME(protector) + " attempts to intercept your "
    + "assault on " + QTNAME(protected) + ", but fails.\n");
    tell_room(environment(protector), QCTNAME(protector) + " fails in "
    + protector->query_possessive() + " attempts to intercept "
    + COMPOSITE_LIVE(targets) + " from attacking " + QTNAME(protected) + ".\n",
    ({ protector, protected }) + targets, protector);
    protector->catch_msg("You fail to intercept " + COMPOSITE_LIVE(targets)
    + " from attacking " + QTNAME(protected) + ".\n");
    protected->catch_msg(QCTNAME(protector) + " fails in "
    + protector->query_possessive() + " attempts to protect you from "
    + COMPOSITE_LIVE(targets) + ".\n");
}

public void
hook_maneuver_limit(object protector, object protected, object *targets)
{
    protected->catch_msg(QCTNAME(protector) + " is too injured to respond to "
    + "your request to guard you in combat.\n");
}

/*
 * Function name: resolve_ability
 * Description:   This gets called when the ability is resolved.
 * Returns:       nothing
 */
static void
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *results)
{
    object  protector, protected,
           *enemies = ({});
    int     success, value;
    value = max(1, min(100, MANAGER->query_ability(actor, TMANEUVER)));
    value = value * items[0]->query_maturity() / 8;
    
    foreach(object target: targets)
    {
        success = actor->resolve_task(TASK_ROUTINE,
            ({ SS_ANI_HANDL, SKILL_VALUE, value, TS_WIS }),
            target, ({ SS_ANI_HANDL, SS_HUNTING, TS_DEX }));
        
        if (success > 0)
            enemies += ({ target });
    }
    
    switch(gManeuver[actor])
    {
        case "retreat":
        protected = items[0];
        protector = actor;
            break;
        case "advance":
        protected = actor;
        protector = items[0];
            break;
        default:
            break;
    }
    
    if (sizeof(enemies) && objectp(protected) && objectp(protector))
    {
        setuid();
        seteuid(getuid());
        
        object maneuver;
        
        if (!protected->has_tamer_maneuver_shadow())
        {
            maneuver = clone_object(SPECIALS + "objects/maneuver_shadow");
            maneuver->shadow_me(protected);
        }
        
        if (protected->set_maneuver_protector(protector))
        {
            if (protector->has_tamer_maneuver_shadow())
                protector->remove_maneuver_enemies();
            
            hook_maneuver_success(protector, protected, enemies);
            protected->set_maneuver_enemies(enemies, protector);
            return;
        }
        
        hook_maneuver_limit(protector, protected, targets);
        return;
    }
    
    hook_maneuver_failed(protector, protected, targets);
    
    MANAGER->add_ability(this_player(), TMANEUVER);
} /* resolve_ability */

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    write("You would be able to maneuver your pet again.\n");
} /* hook_special_complete */

/*
 * Function name: hook_already_active
 * Description:   Called if the player attempts to use the special when active.
 * Returns:       nothing
 */
public void
hook_already_active(object ability)
{
    write("You are already looking for an opportunity to maneuver "+
    "your pet.\n");
} /* hook_already_active */

/*
 * Function name: hook_special_in_cooldown
 * Description:   This gets called if the player attempts to use the ability
 *                when it is in cooldown.
 * Returns:       nothing
 */
public void
hook_special_in_cooldown()
{
    write("You do not see an opportunity to maneuver your pet again.\n");
} /* hook_special_in_cooldown */

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
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    object *onslaught,
            mount;
    string  name;
    
    mount   = MANAGER->query_current_pet(actor);
    name    = MANAGER->query_pet_name(actor->query_real_name());
    
    if (!MANAGER->load_member(actor->query_real_name()) ||
        !strlen(name) || !objectp(mount) ||
        environment(mount) != environment(actor))
    {
        actor->catch_msg("You have no pet to maneuver.\n");
        return 0;
    }
    
    if (mount->query_unconcious())
    {
        actor->catch_msg(QCTNAME(mount) + " is unconscious.\n");
        return 0;
    }
    
    if (actor->query_skill(SS_ANI_HANDL) < 30)
    {
        actor->catch_msg("You wouldn't know how to go about doing that.\n");
        return 0;
    }
    
    if (gManeuver[actor] != "retreat")
    {
        if (actor->query_protector_health_limit(mount))
        {
            actor->catch_msg(QCTNAME(mount) + " is too worn out to guard you "
            + "from further attacks.\n");
            return 0;
        }
        
        if (actor->query_steed() ==  mount)
        {
            actor->catch_msg("You can not maneuver " + QTNAME(mount) + " to "
            + "advance while you are riding " + mount->query_objective()
            + ".\n");
            return 0;
        }
    }
    
    return 1;
} /* check_valid_action */

/*
 * Function name:   do_ability
 * Description:     This is the first function called from the command
 *                  soul.
 * Arguments:       (string) arg - The string used with the ability verb
 * Returns:         Nothing
 */
public int 
do_ability(string arg)
{
    if (!IN_ARRAY(TMANEUVER, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (strlen(arg) && !IN_ARRAY(arg, ({ "advance", "retreat"})))
    {
        notify_fail("Maneuver what? Advance or Retreat?\n");
        return 0;
    }
    
    if (!strlen(arg))
        arg = "retreat";
    
    gManeuver[this_player()] = arg;
    
    return ::do_ability("");
} /* do_ability */


public object *
target_present_enemies(object actor, string str)
{
    object *enemies, mount;

    if (!objectp(mount = MANAGER->query_current_pet(actor)) ||
        environment(actor) != environment(mount))
    {
        actor->catch_msg("You have no pet to maneuver.\n");
        return ({ });
    }
    
    if (gManeuver[actor] == "advance")
        return ::target_present_enemies(actor, str);
    
    enemies = filter(all_inventory(environment(actor)),
              &operator(==)(mount) @ &->query_attack());
    
    if (!sizeof(enemies))
    {
        actor->catch_msg(QCTNAME(mount) + " is not under attack.\n");
        return ({ });
    }
    
    return enemies;
}