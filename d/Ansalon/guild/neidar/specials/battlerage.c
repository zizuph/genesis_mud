/* 
 * Battlerage Ability
 *
 * Neidars have the ability to be flexible in how they fight. By
 * specifying a battlerage, their defence/offense ration shifts.
 * This code used to be in stand_special in the command soul, but
 * has been moved to its own ability in the guild recode.
 *
 * Neidar can battlerage in three different ways:
 *  - fiercely: Normal battleraging, heightened chop
 *  - stubbornly: Extra tanking at the cost of offense
 *  - aggressively: Extra offense at the cost of tanking
 *
 * Created by Petros, May 2009
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

// Prototypes
public int      option_fiercely(object player);
public int      option_aggressively(object player);
public int      option_stubbornly(object player);
public int      is_battleraging_fiercely(object player);
public int      is_battleraging_aggressively(object player);
public int      is_battleraging_stubbornly(object player);

public void 
config_ability()
{
    ::config_ability();
    set_ability_name("battlerage");
    set_ability_offensive(0);
    set_ability_hasted(0); // no haste changes affect the timing of ability
    set_ability_prep_time(30);
    set_ability_cooldown_time(10); // 75% activation time
    set_ability_target(target_actor);    
    set_ability_vocal(0);
    set_ability_visual(0);   
    set_ability_no_stun(0);     
}

public void 
ability_msg(object actor, mixed * targets, string arg)
{
    object br_object;
    
    if (option_fiercely(actor))
    {
        br_object = clone_object(BATTLERAGE_FIERCE);    
    }
    else if (option_aggressively(actor))
    {        
        br_object = clone_object(BATTLERAGE_AGGRESSIVE);    
    }
    else if (option_stubbornly(actor))
    {
        br_object = clone_object(BATTLERAGE_STUBBORN);    
    }
    br_object->set_effect_caster(actor);
    br_object->set_effect_target(actor);
    br_object->move(actor, 1);
    br_object->start();
}

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    send_debug_message("battlerage", "prep time: " + ftoi(prep_time));
    if (is_battleraging_stubbornly(actor))
    {
        send_debug_message("battlerage", "setting attack delay");
        // If this is stubborn, we need to add the attack delay
        actor->inc_prop(LIVE_I_ATTACK_DELAY, ftoi(prep_time));
    }
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
    if (execute)
    {
        // No checks needed on end of the effect
        return 1;
    }

    if (!player->query_attack())
    {
        // put in message to show that you can't battlerage when out of
        // combat
    	player->catch_tell("You are not in battle with anyone, so there "
    	    + "is no point in going into a battlerage.\n");        
        return 0;
    }

    if (!player->query_skill(BATTLERAGING_SKILL))
    {
	    player->catch_tell("Perhaps you should learn how to battlerage "
	        + "like a dwarven warrior first?\n");
        return 0;
    }
    
    // If it passes everything, return success
    return ::check_valid_action(player, targets, arg, execute); 
}

public void
hook_already_active(object ability)
{
    // already battleraging!
    write("You are already raging like a true dwarven warrior!\n");
}

public void
hook_special_preparation_complete()
{
    object player;
    
    player = this_player();
    if (!objectp(player))
    {
        return;
    }
    if (is_battleraging_aggressively(player))
    {
        player->catch_tell("You feel yourself relax from your "
            + "aggressively offensive posture.\n");
    }
    else if (is_battleraging_fiercely(player))
    {
        player->catch_tell("You feel yourself relax from your fiercely "
            + "defensive posture.\n");        
    }
    else if (is_battleraging_stubbornly(player))
    {
        player->catch_tell("You feel yourself relax from your stubbornly "
            + "defensive posture.\n");        
    }    
}

public void
hook_special_complete()
{
    object player;
    object * br_objects, * all_objects;
    
    player = this_player();
    if (!objectp(player))
    {
        return;
    }
    
    all_objects = all_inventory(player);
    br_objects = 
        filter(all_objects, &->is_neidar_battlerage_fierce_object())
      + filter(all_objects, &->is_neidar_battlerage_aggressive_object())
      + filter(all_objects, &->is_neidar_battlerage_stubborn_object());
   
    if (sizeof(br_objects))
    {
        br_objects->remove_object();
    }
        
    // can battlerage again
    write("You feel a surge of adrenaline, and once again feel ready to "
        + "rage like a true dwarven warrior!\n");    
}

public void
hook_special_in_cooldown()
{
    // haven't recovered yet to battlerage again
	write("Patience! You are not ready yet.\n");
}

/*
 * Function:    do_ability
 * Description: This is the first function called from the command
 *              soul. For battlerage, it will handle the different
 *              modes.
 */
public int 
do_ability(string arg)
{
    string adverb, player_name;
    int current_battlerage, new_battlerage;
    
    if (!arg)
    {       
        return ::do_ability("");
    }
    
    player_name = interactive(this_player()) ? 
        this_player()->query_real_name() : OB_NAME(this_player());
    arg = lower_case(arg);
    current_battlerage = OPTIONS_MANAGER->query_option("battlerage",
        player_name);
    switch (arg)
    {
    case "fiercely":
        new_battlerage = 0;
        break;
        
    case "aggressively":
        new_battlerage = 1;
        break;

    case "stubbornly":
        new_battlerage = 2;
        break;
    
    default:
        notify_fail("That doesn't appear to be a way to battlerage!\n");
        return 0;
    }

    if (new_battlerage != current_battlerage)
    {
        OPTIONS_MANAGER->set_option("battlerage", player_name, new_battlerage);
    }
    
    // Start the ability without the argument
    return ::do_ability("");
}

public int
option_fiercely(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return 0;
    }
    
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    if (OPTIONS_MANAGER->query_option("battlerage", name) == 0)
    {
        return 1;
    }
    
    return 0;
}

public int
option_aggressively(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return 0;
    }
    
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    if (OPTIONS_MANAGER->query_option("battlerage", name) == 1)
    {
        return 1;
    }
    
    return 0;
}

public int
option_stubbornly(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return 0;
    }
    
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    if (OPTIONS_MANAGER->query_option("battlerage", name) == 2)
    {
        return 1;
    }
    
    return 0;
}

public int      
is_battleraging_fiercely(object player)
{
    object * br_objects;
    
    br_objects = filter(all_inventory(player), 
        &->is_neidar_battlerage_fierce_object());
    
    if (sizeof(br_objects))
    {
        return 1;
    }
    
    return 0;
}

public int      
is_battleraging_aggressively(object player)
{
    object * br_objects;
    
    br_objects = filter(all_inventory(player), 
        &->is_neidar_battlerage_aggressive_object());
    
    if (sizeof(br_objects))
    {
        return 1;
    }
    
    return 0;
}

public int      
is_battleraging_stubbornly(object player)
{
    object * br_objects;
    
    br_objects = filter(all_inventory(player), 
        &->is_neidar_battlerage_stubborn_object());
    
    if (sizeof(br_objects))
    {
        return 1;
    }
    
    return 0;
}
