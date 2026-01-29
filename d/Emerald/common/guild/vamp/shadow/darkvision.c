/* darkvision.c created by Shiva@Genesis.
 * This file takes care of the vampire's "darkvision" ability.
 * This is part of the vampire guild shadow
 *
 */
#include "../guild.h"

#ifndef NO_DARKVISION

#include "../voptions.h"
#include <macros.h>
#include <stdproperties.h>

#define SW shadow_who

#define DARKVISION_INTERVAL 30
#define MAX_DVIS_LVLS       20

static private int last_time,
                   dvis_lvls;

/* 
 * Function name: reset_darkvision
 * Description:   Calculate the levels of darkvision this vampire
 *                currently needs and add them.  Also, apply any
 *                costs (thirst) accrued since last check.
 *                This function is called A LOT, so keep it simple! 
 */
void reset_darkvision()
{
    int prop;
    int new_lvls, charged_lvls, new_prop, intervals_passed,
        dvis_off = !query_vamp_option(VOPT_DVIS);
    int i;
  
    if (dvis_off && !dvis_lvls)
    {
        // The player has disabled darkvision, and the ability isn't
        // active, so there's nothing to do.
        return;
    }
  
    // Remove appropriate amount of blood 
    if (last_time &&
        (intervals_passed = (time() - last_time) / DARKVISION_INTERVAL))
    {
        // Compute how many levels of darkness we're going to charge the
        // player for seeing through.
        if ((charged_lvls = max(0, dvis_lvls -
            environment(SW)->query_prop(ROOM_I_FREE_VAMP_DVIS))) > 0)
        {
            SW->add_mana(-charged_lvls * intervals_passed);
            for (i = 0; i < intervals_passed; i++)
	    {
                if (!random(12))
		{
                    add_thirst(charged_lvls);
		}
	    }
        }
    }

    if (dvis_off)
    {
        // The player has disabled darkvision, so we'll remove the extra
        // levels of LIVE_I_SEE_DARK
        CP(SW, LIVE_I_SEE_DARK, -dvis_lvls);
        dvis_lvls = 0;
    }
    else
    {
        prop = SW->query_prop(LIVE_I_SEE_DARK);
    
        // Figure how many levels of LIVE_I_SEE_DARK to add/remove
        if ((new_lvls = environment(SW)->light() + prop - 1) > 0)
        {
            /* We have more levels of darkvision than we need;
             * check to make sure we don't remove too many
             */
            new_lvls = MIN(dvis_lvls, new_lvls);
        }
    
        if (new_lvls)
        {
            int free = environment(SW)->query_prop(ROOM_I_FREE_VAMP_DVIS);
            if ((-new_lvls) + dvis_lvls > (MAX_DVIS_LVLS + free))
            {
                if (dvis_lvls)
                {
                    /* The room is darker than we can see in even with
                     * darkvision, so stop darkvision to save blood cost
                     */
                    new_prop = prop - dvis_lvls;
                    dvis_lvls = 0;
                }
            }
            else
            {
                if ((query_max_thirst()-query_thirst()) < (dvis_lvls-new_lvls))
                {
                    // We can't sustain darkvision, so shut it off
                    new_prop = prop - dvis_lvls;
                    dvis_lvls = 0;
                }
                else
                {
                    // Compute the new levels for darkvision and LIVE_I_SEE_DARK
                    dvis_lvls -= new_lvls;
                    new_prop = prop - new_lvls;
                }
            }
      
            SW->add_prop(LIVE_I_SEE_DARK, new_prop);
        }
    }
  
    // Reset time so that costs can be correctly computed later
    if (dvis_lvls)
    {
        if (last_time)
        {
            last_time += intervals_passed * DARKVISION_INTERVAL;
        }
        else
        {
            last_time = time();
        }
    }
    else
    {
        last_time = 0;
    }
}

/* 
 * Function name: add_prop
 * Description:   Recalculate darkvision when the LIVE_I_SEE_DARK
 *                prop is set.
 *                Yes, it's considered bad form to shadow add_prop(),
 *                but the alternative, shadowing add_prop_live_i_see_dark(),
 *                isn't really acceptable.
 * Arguments:     as add_prop on /std/object.c
 */
void add_prop(string prop, mixed val)
{
    SW->add_prop(prop, val);

    if (prop == LIVE_I_SEE_DARK)
    {
        reset_darkvision();
    }
}
#endif  NO_DARKVISION
