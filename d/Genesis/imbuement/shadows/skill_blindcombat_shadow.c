/*
 *  /d/Genesis/imbuement/shadows/skill_blindcombat_shadow.c
 *
 *  Gives a blind-combat boost to wielder
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
    ::init_skillboost(lvl, SS_BLIND_COMBAT, "blindfighting",
        CA_POWER_DESC[lvl] + " clicking sound is coming from this object.");

    set_add_item_array( ({ "sound",
                           "clicking sound",
                           "slight sound",
                           "pronounced sound",
                           "intense sound",
                           "slight clicking sound",
                           "pronounced clicking sound",
                           "intense clicking sound" }) );

    set_add_item_desc("How truly bizarre! An unmistakable clicking"
      + " sound is coming from this object. How could that be possible?\n");

    set_nullstone_type("mole");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The clicking sound coming from the " + shadow_who->short()
        + " comes to an abrupt halt.\n";
} /* dispel_msg_hook */

