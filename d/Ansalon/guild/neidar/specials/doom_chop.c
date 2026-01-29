/* 
 */
inherit "/d/Ansalon/guild/neidar/specials/chop.c";

#include "../guild.h"
#include <ss_types.h>
#include <wa_types.h>

#define DOOM_CHOP_LOG (GUILD_SPECIALS + "doom_chop")

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
    
    /* Doomseeker ability has higher caid */
    set_combat_aid(200);

    /* 10 sec per ability, twice as fast as a normal 
     * Neidar Clan attack */

    set_ability_prep_time(5);
    set_ability_cooldown_time(5);

    set_guild_stat_modifier(SS_OCCUP, 100, 1);
} /* config_ability */

/*
 * 100 is used for racial enemies.
 * 95 is used for normal.
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    object  enemy;
    int     percent, modifier;
    
    enemy = this_player()->query_attack();
    
    /* Calculate the percentage of remaining health */
    percent = this_player()->query_hp() * 100 / this_player()->query_max_hp();
    
    send_debug_message("doomseeker", capitalize(this_player()->query_real_name())+
       " health is at " + percent + "%.");
    
    /* Remove damage based on health */
    modifier = (200 - percent) / 2;

    send_debug_message("doomseeker", capitalize(this_player()->query_real_name())+
       " base chop modifier: " + modifier + ".");
    
    if (!BATTLERAGE_ABILITY->is_battleraging_aggressively(this_player()))
    {
        modifier -= (CHOP_AGGRESSIVE_AID - CHOP_NORMAL_AID);
        send_debug_message("doomseeker", "Not battleraging, reducing total "
            + "to " + modifier + "%.", DOOM_CHOP_LOG);
    }
    
    if (!objectp(enemy) || !is_racial_enemy(enemy))
    {
        // If not a racial enemy, we remove the racial bonus
        modifier -= CHOP_RACIAL_BONUS;
        send_debug_message("doomseeker", "Not a racial enemy, reducing total "
            + "to " + modifier + "%.", DOOM_CHOP_LOG);
    }
   
    send_debug_message("doomseeker", capitalize(this_player()->query_real_name())+ 
       " health is at " + percent + "%, doomseeker chop caid modifier result: " + 
       modifier + "%, (caid of " +(modifier * 2)+ ").", DOOM_CHOP_LOG);
    
    return modifier;
} /* query_combat_aid_modifier */


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
    ::check_valid_action(player, targets, arg, execute);

    int * restrict_list = DOOMSEEKER_BANNED_ARMOURS;
    int restrict_size = sizeof(restrict_list);

    foreach(int armour_type: restrict_list)
    {
        if(armour_type == W_RIGHT || armour_type == W_LEFT)
        {
            if(player->query_armour(armour_type)->query_at() == A_SHIELD)
            {
                object armour_obj = player->query_armour(armour_type);

    	        player->catch_tell("Your death-oath forbids you to wear " +
                    "armours in combat! You will need to remove your " +
                    armour_obj->short()+ " before you can make use of " +
                    "your Doomseeker abilities!\n");
    	        return 0;
            }
        }
        else if(objectp(player->query_armour(armour_type)))
        {
            object armour_obj = player->query_armour(armour_type);

    	    player->catch_tell("Your death-oath forbids you to wear " +
                "armours in combat! You will need to remove your " +
                armour_obj->short()+ " before you can make use of " +
                "your Doomseeker abilities!\n");
    	    return 0;
        }
    }
      
    return ::check_valid_action(player, targets, arg, execute);    
}