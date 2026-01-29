/*
 *  /d/Gondor/rhovanion/mirkwood/obj/effects/stat_bonus.c
 *
 *  Library to apply a skill bonus to an item. This uses the same boosts as
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

#define BOOST_AMOUNT        ({12, 25})

int target_skill;
int applied_bonus;

public void
set_bonus_skill(int skill)
{
    target_skill = skill;
}

public int
query_bonus_skill()
{
    return target_skill;
}


void apply_effect(float multiplier, object player, object source, int level) 
{
    if (applied_bonus > 0) return;

    int max_bonus = BOOST_AMOUNT[level - 1];
    int bonus = ftoi(itof(max_bonus) * multiplier);

    send_debug_message("skill_bonus", sprintf("Max bonus %d, after correction "
        + "%d (%fx)", max_bonus, bonus, multiplier));

    int current_extra = player->query_skill_extra(target_skill);
    int total = player->query_base_skill(target_skill) + current_extra;

    bonus = max(0, min(100, total + bonus) - total);
    if (!total && !player->query_base_skill(target_skill))
    {
        player->set_skill(target_skill, 0);
    }
    player->set_skill_extra(target_skill, current_extra + bonus);

    applied_bonus = bonus;

    send_debug_message("skill_bonus", "Applied skill bonus, new skill "
        + player->query_skill(target_skill));    
}

void remove_effect(object player, object source) 
{
    if (applied_bonus > 0) 
    {
        player->set_skill_extra(target_skill, player->query_skill_extra(target_skill) 
            - applied_bonus);

        send_debug_message("stat_bonus", "Removed skill bonus, new extra skill "
            + player->query_skill_extra(target_skill));

        applied_bonus = 0;
    }
}