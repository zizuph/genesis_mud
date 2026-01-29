/* 
 * Shield of Life Shadow
 *
 * This is the shadow for the Shield of Life. This shadow prevents
 * the player from dying just once before breaking. It also gives
 * back a bit of life as its life energy discharges.
 */

#include "../defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
 
inherit "/std/shadow";

// Global Variables
public object       m_shield_object = 0;

/*
 * Function:    is_life_shield_shadow
 * Description: Always return true to identify the shadow.
 */
public int
is_life_shield_shadow()
{
    return 1;
}

/*
 * Function:    remove_life_shield_shadow
 * Description: Specific function allows removal of this
 *              shadow even when it is layered with other
 *              shadows.
 */
public int
remove_life_shield_shadow()
{
    remove_shadow();
}

public void
initialize_life_shield_shadow(object shield_obj)
{
    m_shield_object = shield_obj;
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    object wearer = query_shadow_who();
    wearer->catch_tell("You see a victorious grin in your enemy's eyes "
        + "and your vision begins to glaze over into the darkness of "
        + "death. Yet, an incredible surge of life rushes up your "
        + "right arm. You suddenly feel much healthier!\n");
    wearer->heal_hp(500);
    
    m_shield_object->remove_broken();
}

 