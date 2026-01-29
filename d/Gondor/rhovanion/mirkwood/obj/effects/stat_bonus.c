/*
 *  /d/Gondor/rhovanion/mirkwood/obj/effects/stat_bonus.c
 *
 *  Library to apply a stat bonus to an item. This uses the same boosts as
 *  imbues, except there is no stacking penalty.
 *
 *  Created by Eowul, Oktober 3rd, 2015
 */

#pragma strict_types;

#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h"

inherit MIRKWOOD_OBJ_DIR + "effects/effect_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define BOOST_AMOUNT        ({18.75, 37.5})
#define BOOST_MIN           ({12, 25})
#define BOOST_MAX           ({37, 75})

int target_stat;
int applied_bonus;

public void
set_bonus_stat(int stat)
{
    target_stat = stat;
}

public int
query_bonus_stat()
{
    return target_stat;
}

/*
 * Function:    calculate_stat_boost
 * Description: Calculate stat boost based on the imbue formulas
 */
private int
calculate_stat_boost(object target, int stat, int bonus_level)
{
    int boost = ftoi(itof(target->query_base_stat(stat)) *
                     (BOOST_AMOUNT[bonus_level-1] / 100.0));
    boost = max(boost, BOOST_MIN[bonus_level-1]);
    boost = min(boost, BOOST_MAX[bonus_level-1]);
    return boost;
}

void apply_effect(float multiplier, object player, object source, int level) 
{
    int max_bonus = calculate_stat_boost(player, target_stat, level);
    int bonus = ftoi(itof(max_bonus) * multiplier);

    send_debug_message("stat_bonus", sprintf("Max bonus %d, after correction "
        + "%d (%fx)", max_bonus, bonus, multiplier));

    applied_bonus = bonus;

    player->set_stat_extra(target_stat, player->query_stat_extra(target_stat) 
        + applied_bonus);

    send_debug_message("stat_bonus", "Applied stat bonus, new extra stat "
        + player->query_stat_extra(target_stat));    
}

void remove_effect(object player, object source) 
{
    if (applied_bonus > 0) 
    {
        player->set_stat_extra(target_stat, player->query_stat_extra(target_stat) 
            - applied_bonus);

        send_debug_message("stat_bonus", "Removed stat bonus, new extra stat "
            + player->query_stat_extra(target_stat));

        applied_bonus = 0;
    }
}