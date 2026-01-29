/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * goblin_std.c
 *
 * This is the object used for players of race Goblin.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/race/generic";
#include "racial_abilities.h"
#include <macros.h>

/*
 * Function name: query_race
 * Description  : Returns the "true" race name of this player.
 * Returns      : string "goblin" - always.
 */
nomask string
query_race()
{
    return "goblin";
}

/*
 * Function name: cr_did_crit
 * Description:   Tells us that we had a critical hit.  This produces critical
 *                hit messages to all relevant parties. This takes place
 *                after cb_did_hit, but before do_die.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description
 *                hid:   The hitlocation id
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *		  dam:	 The damage made in hitpoints
 * Returns:      True if messages were provided for the critical hit. 
 */
public varargs int
cr_did_crit(int aid, string hdesc, int hid, int phurt, object enemy, int dt,
	   int phit, int dam)
{
    if (!HAS_RACIAL_ABILITY(this_object(), OPPORTUNISTIC))
    {
        return ::cr_did_crit(aid, hdesc, hid, phurt, enemy, dt, phit, dam);
    }
    if (dam <= 0)
        return 1;
    this_object()->catch_msg(QCTNAME(enemy) + " recoils in pain as your " +
        "savage attack was more powerful than expected. You feel your " +
        "bloodlust rising!\n");
    enemy->catch_msg("You recoil in pain as " + QTPNAME(this_object()) + 
        " attack was more powerful than expected!\n");
    tell_watcher(QCTNAME(enemy) + " recoils in pain as " + 
        QTPNAME(this_object()) + " attack was more powerful than expected!\n",
        enemy);
    return 1;
}


