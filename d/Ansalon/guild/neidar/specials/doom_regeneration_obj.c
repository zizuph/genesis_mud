#pragma strict_types

#include <ss_types.h>
#include <files.h>
#include <tasks.h>
#include <wa_types.h>
#include <macros.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/regeneration_obj_base";

#define DOOM_REGEN_LOG (GUILD_SPECIALS + "doom_regen")
#define HIS(x)        ((x)->query_possessive())

// Global Variables
static int gAmountHealed = 0;

/*
 * Function Name:   is_neidar_regeneration_object
 * Description:     Indicates whether this is the Neidar Regeneration object.
 *                  Used to identity in filter when adding and removing the
 *                  effect.
 * Arguments:       None
 * Returns:         (int) 1
 */
public int
is_neidar_regeneration_object()
{
    return 1;
} /* is_neidar_regeneration_object */

/*
 * Function Name:   remove_neidar_regeneration_object
 * Description:     Destructor function.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_neidar_regeneration_object()
{
    remove_object();
} /* remove_neidar_regeneration_object */

/*
 * Function Name:   hook_describe_regeneration
 * Description:     Mask this to give messages for when the target gets healed
 *                  by the regeneration effect.
 * Arguments:       (object) target - The regenerating target
 *                  (int) amount - The amount healed.
 * Returns:         Nothing
 */
public void
hook_describe_regeneration(object target, int amount)
{
    /* We want to limit how often the message shows, figured that basing it on
     * the actual amount healed would work well enough.
     */
    gAmountHealed += amount;
    
    if (gAmountHealed < target->query_max_hp() / 5)
        return;
    
    gAmountHealed -= target->query_max_hp() / 5;
    
    target->catch_tell("You swiftly recover from your wounds as the adrenaline "
    + "for battle runs through you.\n");
} /* hook_describe_regeneration */


/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Arguments:       (object) player - player executing special
 * Returns:         number between 1 and 100
 */
public int 
query_combat_aid_modifier(object player)
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    int     modifier;

    modifier = 100 - (player->query_hp() * 100 / player->query_max_hp());
    
    return modifier;
} /* query_combat_aid_modifier */

/*
 * Function Name:   query_regeneration_valid
 * Description:     Validation function to see whether this regeneration object
 *                  is valid in the current situation
 * Arguments:       (object) player - player who is regenerating
 * Returns:         (status) 0 - invalid
 *                  (status) 1 - valid
 */
public status
query_regeneration_valid(object player)
{
    if(player->query_npc())
        return 1;

    /* Prior to regenerating any health, check if the Doomseeker 
       is wearing any armours and provide a panic and mana penalty. */

    int * restrict_list = DOOMSEEKER_BANNED_ARMOURS;
    int restrict_size = sizeof(restrict_list);

    foreach(int armour_type: restrict_list)
    {
        if(armour_type == W_RIGHT || armour_type == W_LEFT)
        {
            if(player->query_armour(armour_type)->query_at() == A_SHIELD)
            {
                object armour_obj = player->query_armour(armour_type);

                if(!random(6))
                {
    	            player->catch_tell("You feel a sense of heightened anxiety " +
                        "in wearing your " +armour_obj->short()+ ", as it goes " +
                        "against your death-oath as a Doomseeker to be " +
                        "armoured!\n");
                    tell_room(environment(player), QCTNAME(player) + " holds "
                        +HIS(player)+ " " +armour_obj->short()+ " awkwardly, " +
                        "a look of discomfort and anxiety on " +HIS(player)+ 
                        " face.\n", ({ player }) );
                    player->add_panic(20);
                    player->add_mana(-10);
    	            return 0;
                }
                return 0;
            }
        }
        else if(objectp(player->query_armour(armour_type)))
        {
            object armour_obj = player->query_armour(armour_type);

            if(!random(6))
            {
    	        player->catch_tell("You feel a sense of heightened anxiety " +
                    "in wearing your " +armour_obj->short()+ ", as it goes " +
                    "against your death-oath as a Doomseeker to be " +
                    "armoured!\n");
                tell_room(environment(player), QCTNAME(player) + " tugs "
                    + "at " +HIS(player)+ " " +armour_obj->short()+
                    ", a look of discomfort and anxiety on " +HIS(player)+ 
                    " face.\n", ({ player }) );

                player->add_panic(20);
                player->add_mana(-10);
    	        return 0;
            }
            return 0;
        }
    }

    return 1;
} /* query_regeneration_valid */

/*
 * Function Name:   create_regeneration
 * Description:     The basic regeneration constructor
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_regeneration()
{
    set_regeneration_combat_aid(94);
    set_regeneration_interval(20); /* 20% of the heal interval = 4sec */
    set_regeneration_peaceful(0);
    set_regeneration_skills(({ BATTLERAGING_SKILL }));
    set_regeneration_stats(({ TS_CON }));
} /* create_regeneration */