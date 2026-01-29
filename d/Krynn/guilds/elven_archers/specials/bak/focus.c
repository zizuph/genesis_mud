/* 
 */

#include <ss_types.h>
#include <composite.h>
#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_name("focus");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(0);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_no_stun(0);
}

/*
 * Function name:   ability_msg
 * Description:     This function displays a message when the ability is being
 *                  activated.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
ability_msg(object actor, mixed * targets, string arg)
{
    setuid();
    seteuid(getuid());
    
    object focus_object, *objects;
           
    objects = filter(all_inventory(actor), &->is_archer_senses_object());
    
    if (!sizeof(objects) || !objectp(focus_object = objects[0]))
        focus_object = clone_object(SENSES);
    
    if (objectp(focus_object))
    {
        if (environment(focus_object) != actor)
        {
            focus_object->set_effect_caster(actor);
            focus_object->set_effect_target(actor);
            focus_object->move(actor, 1);
        }
        focus_object->start_sense(arg);
    }
} /* ability_msg */

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
    if (player->query_skill(SS_FOCUS) < 50)
    {
        player->catch_tell("You lack the capability to maintain your focus.\n");
        return 0;
    }
    
    // If it passes everything, return success
    return ::check_valid_action(player, targets, arg, execute); 
} /* check_valid_action */

/*
 * Function name:   do_ability
 * Description:     The main entry point for abilities
 * Arguments:       (string) arg - the argument passed in for targeting
 * Returns:         (int) 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
        return 0;
     
    if (!strlen(arg = lower_case(arg)) || member_array(arg, FOCUS_LIST) < 0)
    {
        this_player()->catch_tell("You are not familiar with that way of "
        + "focusing. You can focus on " + COMPOSITE_WORDS(FOCUS_LIST) + ".\n");
        return 1;
    }

    return ::do_ability(arg);
} /* do_ability */

/*
 * Function name:   hook_special_complete
 * Description:     This gets called whenever the special is ready again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_complete()
{
    // Dont display a message
} /* hook_special_complete */