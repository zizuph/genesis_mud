/*
 * Armoury Master Shadow
 * 
 * When a Neidar is wearing a full set of armours, they get the
 * special armoury bonus. This code will be the one that gives the
 * messages when they activate or deactivate the ability.
 *
 * Petros, April 2009
 */
 
#pragma strict_types 

#include <wa_types.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public int      is_fully_armoured();

// Global Variables
public int      check_alarm = 0;
public int      old_state   = 0;

public int
has_armour_master_shadow()
{
    return 1;
}

public void
remove_armour_master_shadow()
{
    remove_shadow();
}

public void
check_fully_armoured(object player, object arm)
{
    int new_state;

    new_state = is_fully_armoured();    
    if (old_state && !new_state)
    {
        player->catch_tell("You feel more vulnerable as you "
            + "remove the " + arm->short() + ".\n");
    }
    else if (new_state && !old_state)
    {
        player->catch_tell("You gain mastery over all your armour "
            + "as you strap on the " + arm->short() + ", greatly "
            + "protecting yourself from your enemies.\n");
    } 
}

/*
 * Function name:   remove_arm
 * Description:     Remove an armour
 * Arguments:       arm - The armour.
 */
public void
remove_arm(object arm)
{
    if (!get_alarm(check_alarm))
    {
        old_state = is_fully_armoured();
    }
    else
    {
        remove_alarm(check_alarm);
    }
    check_alarm = set_alarm(0.0, 0.0, 
        &check_fully_armoured(shadow_who, arm));

    shadow_who->remove_arm(arm);    
}

/*
 * Function name: wear_arm
 * Description:   wear an armour
 * Arguments:     The armour to be worn
 * Returns:       string - error message (armour could not be worn)
 *                1 - success (armour was worn)
 */
public mixed
wear_arm(object arm)
{
    if (!get_alarm(check_alarm))
    {
        old_state = is_fully_armoured();
    }
    else
    {
        remove_alarm(check_alarm);
    }
    check_alarm = set_alarm(0.0, 0.0, 
        &check_fully_armoured(shadow_who, arm));
    
    return shadow_who->wear_arm(arm);    
}

public int
is_fully_armoured()
{
    // One is fully armoured when one has the following slots
    // covered:
    //    - Head
    //    - Chest
    //    - Legs
    //    - Right and Left Arms
    //    - At least one shield
    object * armours = shadow_who->query_armour(-1);
    int bHasShield = 0;
    int coveredSlots = 0;
        
    foreach (object armour : armours)
    {
        if (armour->query_at() == A_SHIELD)
        {
            bHasShield = 1;
            continue;
        }
        
        coveredSlots |= armour->query_at();
    }
    
    coveredSlots &= TS_HBODY;
    if (coveredSlots == TS_HBODY
        && bHasShield)
    {
        return 1;
    }
    
    return 0;
}
