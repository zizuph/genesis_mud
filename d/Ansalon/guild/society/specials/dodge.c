/*
 * Dodge special for Secret Society of Kenders.
 * 
 */
 
#pragma strict_types

inherit "/d/Genesis/specials/timed_ability";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"

#include "../guild.h"

public int
do_ability(string arg)
{
    string opt;
    status off;
    
    if (strlen(arg) && parse_command(arg, ({}), "'brief' %w", opt))
    {
        if ((off = member_array(opt, ({"off", "on"}))) > -1)
        {
            this_player()->set_dodge_brief(off);
            write("Dodge brief:   " + capitalize(off) + "\n");
            return 1;
        }
    }
    
    return ::do_ability(arg);
}

public void
config_ability()
{
    ::config_ability();
    set_ability_name("dodge");
    set_ability_hasted(0);
    set_ability_offensive(0);
    set_ability_prep_time(30);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);
}

public void
remove_kender_dodge(object actor)
{
    object *evades;

    if (!actor->has_evade_shadow())
    {
        return;
    }

    // Remove all existing evades first
    evades = actor->query_evade_effects() + all_inventory(actor);
    evades = filter(evades, &->is_kender_dodge());
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
    
    write("You stand on the balls of your feet, ready for any blows " +
    "that come your way.\n");
    
    // Remove all existing evades first
    remove_kender_dodge(actor);
    
    evade_obj = clone_object(DODGE_OBJ);
    evade_obj->set_effect_caster(actor);
    evade_obj->set_effect_target(actor);
    evade_obj->move(actor, 1);
    evade_obj->start();
}

static void
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *results)
{
    remove_kender_dodge(actor);    
}

public void
hook_special_complete()
{
    write("\nYou feel ready to dodge again.\n\n");    
}

public void
hook_already_active(object ability)
{
    write("You are already dodging!\n");
}

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    int skill;
    
    skill = player->query_skill(SS_CTACT_SPECIAL);

    /* Temporary Solution*/
    if ("/d/Ansalon/guild/society/wimpy_check.c"->wimp_check(player) < player->query_whimpy())
    {
        write("You are too busy thinking about running away to " +
        "compose a taunt.\n");
        return 0;
    }
    
    if (!player->query_attack())
    {
        player->catch_msg("You aren't in combat!\n");
        return 0;
    }
    
    if (skill < 1)
    {
        player->catch_msg("You attempt to dodge, but stumble over your own " +
        "feet in the process.\n");
        return 0;
    }
    
    if (query_ability_active(player))
    {
        hook_already_active(this_object());
        return 0;
    }

    return 1;
}

public varargs string
query_restricted_ability_message(string ability, object player)
{
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
    object *enemies,
            enemy;
    
    if (!execute && !validate_requirements(player))
    {
        // Only need to validate requirements at the beginning, not at
        // the end.
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}