/*
 *  /d/Genesis/imbuement/shadows/skill_sneakhide_shadow.c
 *
 *  Gives a sneak and hide boost to wielder
 *
 *  2010/09/15 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "skill_base";

/* Definitions */

/* Global Variables */
public int               Secondary_Boost = 0;

/* Prototypes */
public void              init_imbue_shadow(int lvl);

/*
 * Function name:        init_imbue_shadow
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 */
public void
init_imbue_shadow(int lvl)
{   
    ::init_skillboost(lvl, SS_SNEAK, "sneak and hide", "It is emitting "
        + A_POWER_DESC[lvl] + " purring sound.");

    set_add_item_array( ({ "sound",
                           "purring sound",
                           "slight sound",
                           "pronounced sound",
                           "intense sound",
                           "slight purring sound",
                           "pronounced purring sound",
                           "intense purring sound" }) );

    set_add_item_desc("How truly bizarre! An unmistakable purring"
      + " sound is coming from this object. How could that be possible?\n");

    set_nullstone_type("rodent");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The purring sound coming from the " + shadow_who->short()
        + " comes to an abrupt halt.\n";
} /* dispel_msg_hook */

/*
 * Function:    remove_boost
 * Description: Call to actually remove the boost
 */
public void
remove_boost()
{
    if (Secondary_Boost == 0)
    {
        ::remove_boost();
        return;
    }

    // For sneak shadow, we also add hide as well
    object owner = query_owner();
    int current_extra = owner->query_skill_extra(SS_HIDE);
    owner->set_skill_extra(SS_HIDE, current_extra - Secondary_Boost);
    Secondary_Boost = 0; // reset boost
    ::remove_boost();
}

/*
 * Function:    add_boost
 * Description: Adds the boost to the owner. The argument of
 *              factor applies when there are multiple boosts for
 *              the same imbue. We topologically sort the boosts
 *              and reduce the power for each successive boost.
 */
public void
add_boost(int factor = 0)
{
    ::add_boost(factor);

    // For sneak shadow, we also add hide as well.
    object owner = query_owner();
    Secondary_Boost = ftoi(itof(calculate_boost()) * pow(0.62, itof(factor)));
    int current_extra = owner->query_skill_extra(SS_HIDE);
    int total = owner->query_base_skill(SS_HIDE) + current_extra;
    // We need to adjust boost if it causes the skill to exceed 100
    Secondary_Boost = max(0, min(100, total + Secondary_Boost) - total);
    // There is a flaw in /std/living for skills that haven't been instantiated
    // We instantiate it so that it will display properly in the player
    if (!total && !owner->query_base_skill(SS_HIDE))
    {
        owner->set_skill(SS_HIDE, 0);
    }
    owner->set_skill_extra(SS_HIDE, current_extra + Secondary_Boost);
}


