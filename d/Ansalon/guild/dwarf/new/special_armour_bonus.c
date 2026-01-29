/*
 * Neidar Armour Bonus
 * 
 * Neidar gain a 10% combat aid damage absorbtion bonus
 * when fully armoured.
 *
 * Defined as armour covering head, body, arms, legs, and a shield. 
 * 
 * Louie Nov 2008
 *
 */
 
#pragma strict_types

//#include "defs.h"
#include "/d/Genesis/specials/defs.h"
#include "guild.h"

//inherit DAM_MOD_BASE_OBJ;
inherit "/d/Genesis/specials/std/dam_mod_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

//#include DEBUGGER_TELL
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
    set_name("_neidar_armour_bonus_object_");
    add_name( ({"neidar_armour_bonus_obj" }) );
    set_short("Armour bonus object for Neidar Clan");    
    set_long("The Armour Bonus object for Neidar Clan members.  You shouldn't "+
        "see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(ARMOUR_BONUS_AID);

}                           

/*
 * Function     : remove_neidar_armour_bonus_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_armour_bonus_object()
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
    //Neidar gain an armour bonus when fully armoured:
    //Must have head, body, arms, legs, and shield slots protected.
    int shield_found = 0;
    object test_ob;
    if (!player->query_armour(TS_HEAD)) {
        return 0;
    }

    if (!player->query_armour(TS_CHEST)) {
        return 0;
    }

    if (!player->query_armour(TS_LEGS)) {
        return 0;
    }

    if (!player->query_armour(TS_RARM)) {
        return 0;
    }

    if (!player->query_armour(TS_LARM)) {
        return 0;
    }

    if ((test_ob = player->query_armour(TS_RWEAPON))) {
        if (test_ob->query_at(A_SHIELD)){
            shield_found = 1;
        }
    }

    if ((test_ob = player->query_armour(TS_LWEAPON))) {
        if (test_ob->query_at(A_SHIELD)){
            shield_found = 1;
        }
    }

    if (!shield_found) {
        return 0;
    }

    return 1;
}
