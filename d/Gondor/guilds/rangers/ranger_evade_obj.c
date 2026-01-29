/*
 * /d/Gondor/guilds/rangers/ranger_evade_obj.c
 *
 * Ranger evade object.  Provides 20 CAID, always on.
 *
 */

#include <tasks.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit EVADE_OBJ_BASE;
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

public void ranger_blocked(object player, object attacker, int attack_id);

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    

    ::create_effect();

    set_evade_stats(BRAWL_STATS);
    set_evade_skills(BRAWL_SKILLS);
    // 25% combat aid == 20% evade
    set_evade_combat_aid(20);
    set_blocked_function(ranger_blocked);
    set_short("hidden ranger evade object");
}

/*
 * Function     : ranger_blocked
 */
public void
ranger_blocked(object player, object attacker, int attack_id)
{
    player->catch_msg("You weave suddenly and avoid the attack of "
        + QTNAME(attacker)+".\n");
    attacker->catch_msg(QCTNAME(player) + 
        " weaves suddenly and avoids your attack.\n");
    tell_room(QCTNAME(player) + " weaves suddenly and avoids the "  +
        "attack of " + QTNAME(attacker) + ".\n",
        ({ player, attacker }), player);
}
