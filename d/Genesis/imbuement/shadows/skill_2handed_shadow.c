/*
 *  /d/Genesis/imbuement/shadows/skill_2handed_shadow.c
 *
 *  Gives a two-handed combat boost to wielder
 *
 *  2010/09/15 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "skill_base";

/* Definitions */

/* Global Variables */

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
    ::init_skillboost(lvl, SS_2H_COMBAT, "two-handed combat",
        "It pulses with " + A_POWER_DESC[lvl] + " silvery aura.");

    set_add_item_array( ({ "aura",
                           "silvery aura",
                           "slight aura",
                           "pronounced aura",
                           "intense aura",
                           "slight silvery aura",
                           "pronounced silvery aura",
                           "intense silvery aura" }) );

    set_add_item_desc("The air surrounding this object pulses with an"
      + " uncanny silvery hue. What magic is at work here?\n");

    set_nullstone_type("twin");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The silvery aura fades from the " + shadow_who->short()
        + " and is gone.\n";
} /* dispel_msg_hook */

