/*
 *
 */

inherit "/d/Genesis/specials/std/dam_mod_obj_base";
 
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
    set_name("_vampires_resilience_obj");
    add_name( ({"vampires_resilience_obj" }) );
    set_short("hidden vampires resilience object");    
    set_long("The vampires resilience object for the Vampires.  You shouldn't "+
        "see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(38);
}                           

/*
 * Function:    is_neidar_armour_master_object
 * Description: Indicates whether this is the Neidar Armour Master
 *              Object. Used in filters during remove_object
 */
public int
is_vampires_resilience_object()
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
remove_vampires_resilience_object()
{
    remove_object();
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
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(player->query_name()) == 2)
    {
        return 1;
    }

    return 0;
}