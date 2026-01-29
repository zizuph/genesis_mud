/*
 *  /d/Genesis/imbuement/shadows/skill_death_shadow.c
 *
 *  Gives a death magic boost to wielder
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
    ::init_skillboost(lvl, SS_ELEMENT_DEATH, "death magic", "Its surface has "
        + A_POWER_DESC[lvl] + " grey tint.");

    set_add_item_array( ({ "tint",
                           "grey tint",
                           "slight tint",
                           "pronounced tint",
                           "intense tint",
                           "slight grey tint",
                           "pronounced grey tint",
                           "intense grey tint" }) );

    set_add_item_desc("There is a strange grey tint to this object. The"
      + " colour actually seems to shimmer slightly as you look at it.\n");

    set_nullstone_type("corpse");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The grey tint fades from the " + shadow_who->short()
        + " and is gone.\n";
} /* dispel_msg_hook */
