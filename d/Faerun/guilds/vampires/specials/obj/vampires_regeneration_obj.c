/*
*
*/
inherit "/d/Genesis/specials/std/regeneration_obj_base";

#include <ss_types.h>
#include <files.h>
#include <tasks.h>
#include <wa_types.h>
#include <macros.h>
#include "../../guild.h"

#define VAMP_SUNLIGHT_TOLERANCE 5




// Global Variables
static int gAmountHealed = 0;


/*
 * Function:    query_sunlight_level
 * Description: This checks a room for the amount of sunlight that is in
 *              it. It uses the Genesis Timekeeper's code to do most of
 *              the sunlight calculations.
 */
public int
query_sunlight_level(object room)
{
    object player = environment(this_object());
    
    setuid();
    seteuid(getuid());    
    
    int sunlight = GENESIS_TIMEKEEPER->query_sunlight(player);
    
    if (sunlight < VAMP_SUNLIGHT_TOLERANCE
      || room->query_prop(OBJ_I_LIGHT) <= 0)
    {
        // If the room itself is dark, or sunlight levels are too low,
        // we allow the vampire to heal from any burning that they may
        // have encountered by returning 0 for the sunlight levels
        return 0;
    }
    
    return sunlight;    
}


/*
 * Function Name:   is_vampires_regeneration_object
 * Description:     Indicates whether this is the Vampires Regeneration object.
 *                  Used to identity in filter when adding and removing the
 *                  effect.
 * Arguments:       None
 * Returns:         (int) 1
 */
public int
is_vampires_regeneration_object()
{
    return 1;
} 


/*
 * Function Name:   remove_vampires_regeneration_object
 * Description:     Destructor function.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_vampires_regeneration_object()
{
    remove_object();
}


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
	int currenthp;
	
	currenthp = target->query_hp();
    
    if (target->query_ghost())
    {
        return;
    }
	
	if (target->query_max_hp() != currenthp)
	{
        int sunlight = query_sunlight_level(environment(target));
               
        if (!sunlight)
        {
            int dice = random(5);
                       
            // Only Occ vampires gets the full caid
            if (VAMPIRES_MASTER->is_occ_vampires(target->query_name()))
            {
                // Occ regen, combat, 20 caid                    
                if (dice == 1)
                {
                    target->catch_tell("Your undead flesh knits together, closing your wounds.\n");
                }
                
                return;
            }
            
            // Layman regen, 10 caid
            if (dice == 1)
            {
                target->catch_tell("Your undead flesh slowly knits together, closing your wounds.\n");
            }
            
            return;
        }
	}
} 


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
    int total_combat_aid = 0;  
    
    int modifier = 100;
    
    int sunlight = query_sunlight_level(environment(player));
             
    // Regeneration only works when not exposed to sunlight
    if (!sunlight)
    {       
        // Only Occ vampires gets the full caid
        if (VAMPIRES_MASTER->is_occ_vampires(player->query_name()))
        {
            return modifier;
        }
        
        // Laymans only get 10 caid regen.
        modifier -= 50;
         
        return modifier;        
    }

    // If we are exposed to sunlight, the regeneration will
    // be at a minimum.
    modifier = 1;
    
    return modifier;
} 


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
    set_name("_vampires_regeneration_obj");
    add_name( ({"vampires_regeneration_obj" }) );
    set_short("hidden vampires regeneration object");    
    set_long("This is the secret and extremely hidden vampires regeneration object.\n");
    set_regeneration_combat_aid(20);
    set_regeneration_interval(20); /* 20% of the heal interval = 4sec */
    set_regeneration_peaceful(0);
    set_regeneration_skills(({ SS_ANATOMY }));
    set_regeneration_stats(({ TS_CON }));
} /* create_regeneration */