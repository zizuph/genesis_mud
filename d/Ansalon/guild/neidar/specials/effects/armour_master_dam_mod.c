/*
 * Neidar Armour Master
 * 
 * Neidar gain a 10% combat aid damage absorbtion bonus
 * when fully armoured.
 *
 * Defined as armour covering head, body, arms, legs, and a shield. 
 * 
 * Created by Louie Nov 2008
 * Modified by Petros, April 2009
 */
 
#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../guild.h"
#include "/d/Genesis/specials/new/defs.h"

inherit DAM_MOD_OBJ_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_neidar_armour_master_object_");
    add_name( ({"neidar_armour_master_obj" }) );
    set_short("hidden neidar armour master object");    
    set_long("The Armour Master object for Neidar Clan members.  You shouldn't "+
        "see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(ARMOUR_MASTER_AID);
}                           

/*
 * Function:    is_neidar_armour_master_object
 * Description: Indicates whether this is the Neidar Armour Master
 *              Object. Used in filters during remove_object
 */
public int
is_neidar_armour_master_object()
{
    return 1;
}

/*
 * Function     : remove_neidar_armour_master_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_armour_master_object()
{
    remove_object();
}

/*
 * Function:    is_fully_armoured
 * Description: Checks all the armour that is worn to see if
 *              it fills all the slots of TS_HBODY and also
 *              includes a shield.
 */
public int
is_fully_armoured(object player)
{
    // One is fully armoured when one has the following slots
    // covered:
    //    - Head
    //    - Chest
    //    - Legs
    //    - Right and Left Arms
    //    - At least one shield
    object * armours = player->query_armour(-1);
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

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    return is_fully_armoured(player); 
}

/*
 * Function name: start
 * Description:   Start up the effect. We override this method so that we
 *                can add the armour master shadow.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    int result;
    object player;
    
    result = ::start();
    // Add the armour master shadow to indicate when they are fully armoured
    if (objectp(player = environment(this_object()))
        && IS_LIVING_OBJECT(player)
        && !player->has_armour_master_shadow())
    {
        clone_object(ARMOUR_MASTER_SH)->shadow_me(player);
    }
    
    return result;
}

public void
remove_object()
{
    object player;
    object * objs;
    
    if (objectp(player = environment(this_object()))
        && IS_LIVING_OBJECT(player))
    {
        // Check to see how many armour master objects there are
        objs = filter(all_inventory(player), &->is_neidar_armour_master_object());
        if (sizeof(objs) == 1)
        {
            // If we're removing the only one left, we remove the shadow
            player->remove_armour_master_shadow();
        }
    }
    
    ::remove_object();
}
