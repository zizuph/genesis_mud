/*
 * Base Effect Object
 * 
 * This is the base effect object that handles effects in conjunction
 * with the effects shadow. Effect objects stack with one another.
 *
 * Created by Petros, June 2008
 *
 * Modified on 2021-03-06 by Carnak:
 * - Simplified the scaling of effects.
 *
 * Zizuph - 2022-06-15
 * - Migrated combat aid, percentage and likelyhood logic to here.
 *   Drop effect_combat_strength, which was percentage based and
 *   more difficult to add effects with.
 */
 
#pragma strict_types

#include "defs.h"

inherit "/std/object";
inherit TASK_MODIFIERS_LIB;
inherit EFFECT_OBJECT_LIB;
inherit SPECIALS_DIR + "calculations";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         set_effect_combat_aid(int caid);

// Global Variables
private int         Effect_combat_aid;
private mixed       Skills_used;
private mixed       Stats_used;
private object *    Shadow_list;
private int         Effect_likelyhood = 100;

/*
 * Function     : set_effect_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the effect
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_effect_skills(mixed skills)
{
   Skills_used = skills;   
} /* set_effect_skills */

/*
 * Function     : query_effect_skills
 * Description  : Returns the skills being used to calculate effect 
 *                strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_effect_skills()
{
    return Skills_used;
} /* query_effect_skills */

/*
 * Function     : set_effect_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the effect
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_effect_stats(mixed stats)
{
   Stats_used=stats;   
} /* set_effect_stats */

/*
 * Function     : query_effect_stats
 * Description  : Returns the stats being used to calculate effect 
 *                strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_effect_stats()
{
    return Stats_used;
} /* query_effect_stats */

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
} /* create_effect */

/*
 * Function     : create_object
 * Description  : Creates the base effect object
 * Arguments    : none
 * Returns      : nothing
 */
public nomask void
create_object()
{
    set_name("_base_effect_object_");
    add_name( ({"base_effect_obj" }) );
    set_short("hidden base effect object");    
    set_long("A basic effect object. One should not be able to see it "
           + "in their inventory.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    setuid();
    seteuid(getuid());

    Shadow_list = ({ });
    
    create_effect();
} /* create_object */

/*
 * Function     : set_effect_combat_aid
 * Description  : Sets the effect combat aid which is used to determine
 *                the effect percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_effect_combat_aid(int caid)
{
    Effect_combat_aid = caid;
} /* set_effect_combat_aid */

/*
 * Function     : query_effect_combat_aid
 * Description  : returns the effect combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_effect_combat_aid(object player)
{
    return Effect_combat_aid;
} /* query_effect_combat_aid */

/*
 * Function     : set_effect_likelyhood
 * Description  : Set the likelyhood that the effect goes off.
 * Arguments    : likelyhood that the effect goes off.
 */
public void
set_effect_likelyhood(int likelyhood)
{
    Effect_likelyhood = max(1, min(100, likelyhood));
}

/*
 * Function     : query_effect_likelyhood
 * Description  : returns the likelyhood the effect goes off
 * Returns      : percentage chance of the effect.
 */
public int
query_effect_likelyhood()
{
    return Effect_likelyhood;
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier(object player)
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return 100;
} /* query_combat_aid_modifier */

public nomask int
query_effect_modified_combat_aid(object player)
{
    int effect, skill_modifier, stat_modifier, aid_modifier;
    
    skill_modifier = calc_base_skill(player, query_effect_skills());

    send_debug_message("base_effect_obj", sprintf("Base modifier %d",
                     skill_modifier));

    
    // Stat modifier has been removed.
    // stat_modifier = calc_stat_modifier(player, query_effect_stats());
    aid_modifier = min(100, query_combat_aid_modifier(player));
    effect = query_effect_combat_aid(player);
    return effect * skill_modifier * aid_modifier 
        / 100 / query_effect_likelyhood();
}

/*
 * Function     : query_effect_percentage
 * Description  : Returns the max percentage set during creation
 * Arguments    : none
 * Returns      : the evasion percentage
 */
public nomask int 
query_effect_percentage(object player)
{
    int caid = query_effect_modified_combat_aid(player);
    return convert_caid_to_percentage(caid);
} /* query_effect_percentage */

/*
 * Function     : query_effect_valid
 * Description  : Validation function to see whether this effect object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_effect_valid(object player, object attacker, int attack_id)
{
    return 1;
} /* query_effect_valid */

/*
 * Function     : remove_shadow_from_list
 * Description  : Each effect object keeps track of the shadows
 *                that are using it. One example of this is the
 *                AA evade. It uses one evade object for multiple
 *                people.
 * Arguments    : obj - the shadow that is using this effect
 * Returns      : 0/1 - successfully removed or not.
 */
public int
remove_shadow_from_list(object obj)
{
    if (IN_ARRAY(obj, Shadow_list))
    {
        Shadow_list -= ({ obj });
        return 1;
    }
    
    return 0;
} /* remove_shadow_from_list */

/*
 * Function     : add_shadow_to_list
 * Description  : Each effect object keeps track of the shadows
 *                that are using it. One example of this is the
 *                AA evade. It uses one evade object for multiple
 *                people.
 * Arguments    : obj - the shadow that is using this effect
 * Returns      : 0/1 - successfully added or not.
 */
public int
add_shadow_to_list(object obj)
{
    if (!IN_ARRAY(obj, Shadow_list))
    {
        Shadow_list += ({ obj });
        return 1;
    }
    
    return 0;
} /* add_shadow_to_list */

/*
 * Function     : query_shadow_list
 * Description  : Gets the list of shadows that are using this effect
 * Arguments    : none
 * Returns      : the array of shadows that are using this effect
 */
public object *
query_shadow_list()
{
    return Shadow_list;
} /* query_shadow_list */


/*
 * Function     : enter_env
 * Description  : When the effect object enters the inventory, it will
 *                set the effect target of the living that it is entering.
 *                This is a convenience as this is the case for most
 *                effects.
 * Arguments    : dest - where the object is entering
 *                old  - where the object came from
 * Returns      : nothing
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest && living(dest) && !query_effect_target())
    {
        send_debug_message("base_effect_obj", "Entering living "
                         + "environment. Setting effect target to "
                         + "container.");
        set_effect_target(dest);
    }        
} /* enter_env */
