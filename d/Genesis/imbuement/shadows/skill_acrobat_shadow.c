/*
 *  /d/Genesis/imbuement/shadows/skill_acrobat_shadow.c
 *
 *  Gives a acrobat boost to wielder
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
    ::init_skillboost(lvl, SS_ACROBAT, "acrobat", "You notice "
        + A_POWER_DESC[lvl] + " twisting pattern dancing off its surface.");

    set_add_item_array( ({ "pattern",
                           "twisting pattern",
                           "slight pattern",
                           "pronounced pattern",
                           "intense pattern",
                           "slight twisting pattern",
                           "pronounced twisting pattern",
                           "intense twisting pattern" }) );

    set_add_item_desc("The surface of this object seems to be " +
        "twisting in a strange pattern. You become dizzy looking " +
        "at the pattern!\n");

    set_nullstone_type("leap");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The twisting pattern fades from the surface of the "
      + shadow_who->short() + " and disappears.\n";
} /* dispel_msg_hook */

