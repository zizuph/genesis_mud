
inherit "/d/Genesis/specials/new/effects/boons/evade_obj_base";

#include "special.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    //Evade combat aid is overridden with query_evade_combat_aid
    //For the various scenarios

    set_evade_skills(({ SS_SWAY }));
    set_evade_stats(({ SKILL_AVG, TS_DEX, SKILL_END }));

    set_evade_combat_aid(SWAY_EVADE_CAID);
    set_name(SWAY_EVADE_OBJ);
}

public void
attack_blocked(object player, object attacker, int att_id)
{
    int encumb = player->query_encumberance_weight();
    if (encumb >= ENCUMB_FLING) {
		player->catch_msg("You danced out of reach, but just barely, "+
			"as you are nearly too encumbered to do so.\n");
      // Message that encumberance is hindering defensiveness.
    }
    else {
        player->catch_msg("Deep in the Sway, you follow the "+
		    "guidance of the voices cautioning you to move NOW "+
			"and you do, dancing just beyond the reach of "+ 
			QTNAME(attacker) +".\n");
    }
    attacker->catch_msg(QCTNAME(player) +
        " dances out of reach, causing you to miss.\n");
	tell_room(ENV(player), QCTNAME(player) +" dances beyond "+
	    "the reach of "+ QTNAME(attacker) +".\n", ({player, attacker}));
}


public int
query_evade_valid(object player, object attacker, int attack_id)
{
    return 1;
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
    int percentage;
    switch (player->query_prop(SWAY_PHASE_PROP)) {
      // 10 seconds at 25% effect.
      case 1:  percentage = 25;
        break;
      // 35 seconds at 50% effect.
      case 2:
      case 3:  percentage = 50;
        break;
      // 55 seconds at 100% effect.
      case 4:
      case 5:  percentage = 100;
        break;
      default: return 0;
    }
    int encumb = player->query_encumberance_weight();
    int mod;
    if (encumb >= ENCUMB_FLING)
    {
        mod = EFF_REDUCE(encumb, ENCUMB_FLING);
        percentage -= mod;
    }
    percentage = MAX(0, percentage);
    return percentage;
} /* query_combat_aid_modifier */
