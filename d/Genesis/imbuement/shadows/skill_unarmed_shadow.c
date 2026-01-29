/*
 *  /d/Genesis/imbuement/shadows/skill_unarmed_shadow.c
 *
 *  Gives an unarmed combat boost to wielder
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
    ::init_skillboost(lvl, SS_UNARM_COMBAT, "unarmed combat",
        "It is pulsing with the " + POWER_DESC[lvl] + " aura of a monkey.");

    set_add_item_array( ({ "monkey-like aura",
                           "monkey aura",
                           "aura",
                           "aura of a monkey",
                           "slight aura",
                           "pronounced aura",
                           "intense aura",
                           "slight aura of a monkey",
                           "pronounced aura of a monkey",
                           "intense aura of a monkey" }) );

    set_add_item_desc("This is one of the most unusual things you have"
      + " ever tried to understand. Looking at this object, you actually"
      + " get the feeling that ... a monkey is present!\n");

    set_nullstone_type("palm");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The monkey-like aura fades from the " + shadow_who->short()
        + " and is gone.\n";
} /* dispel_msg_hook */