/*
 * File Name        : sword.c
 * By               : Boron
 * Inspiration from : -
 * Date             : March 2001.
 * Description      : The shadow to the swords, it contains the guild special.
 *
 */
inherit "/std/shadow";

#include "/d/Krynn/common/defs.h"
#include "../locals.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
setup_things()
{
    // Todo, setup things here so the special will work.
}


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;

    wielder = shadow_who->query_wielded();


    if ((wielder->sentry_special(OFFENSIVE) && (random(1) )
        && (dam > 0))
    {

       dam = dam / 2;
       enemy->heal_hp(-dam);

    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

