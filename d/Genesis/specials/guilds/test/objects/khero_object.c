/*
 * Standard Kheroism Object
 *
 * Simulates the Stat Increases for Knight Kheroism
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public int      strength_bonus;
public int      discipline_bonus;

// Prototypes
public void     start_heroism_benefits(object player);
public void     remove_heroism_benefits(object player);

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("standard_khero_object");
    set_short("standard khero object");
    set_long("This is a kheroism object for Knight testing.\n");
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    send_debug_message("khero_object", "Entering inventory");
    if (to != from && IS_LIVING_OBJECT(to))
    {
        start_heroism_benefits(to);
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    send_debug_message("khero_object", "Leaving inventory");
    if (old != dest && IS_LIVING_OBJECT(old))
    {
        remove_heroism_benefits(old);
    }
}


// Utility Functions for Determining Bonus. These are the same
// Functions that are being used by Gladiators
public int
query_stat_bonus(object player, int stat)
{
    // The goal of this function is to increase the F_STR_FACTOR aid
    // by 20%. This is done by modifying and plugging in the numbers
    // based on the current F_STR_FACTOR formula: ((600 + (str) * 4) / 10)    
    int base, modifier;
    float boost;
    
    base  = player->query_base_stat(stat);
    boost = 1.20; // gives 20% bonus
    modifier = ftoi(150.0 * (boost - 1.0) + (itof(base) * boost));    
    
    return modifier - base;
}

static int
query_str_bonus(object player)
{
    return query_stat_bonus(player, SS_STR);
}

static int
query_dis_bonus(object player)
{
    return query_stat_bonus(player, SS_DIS);
}

public void
start_heroism_benefits(object player)
{
    // Heroism has a few benefits
    // 1. Adds 100 Quickness to the Knight
    player->add_prop(LIVE_I_QUICKNESS,
        player->query_prop(LIVE_I_QUICKNESS) + 100);
    // 2. Increases their Strength and Discipline by 50%
    strength_bonus = query_str_bonus(player);
    player->set_stat_extra(SS_STR, 
        player->query_stat_extra(SS_STR) + strength_bonus);
    discipline_bonus = query_dis_bonus(player);
    player->set_stat_extra(SS_DIS,
        player->query_stat_extra(SS_DIS) + discipline_bonus);        
}

public void
remove_heroism_benefits(object player)
{
    // At the end of Heroism, we need to revert all the additions
    // 1. Remove 100 Quickness from the Knight
    player->add_prop(LIVE_I_QUICKNESS,
        player->query_prop(LIVE_I_QUICKNESS) - 100);
    // 2. Decrease their Strength and Discipline back to normal
    player->set_stat_extra(SS_STR, 
        player->query_stat_extra(SS_STR) - strength_bonus);
    player->set_stat_extra(SS_DIS,
        player->query_stat_extra(SS_DIS) - discipline_bonus);
}
