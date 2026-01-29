/*
 *  /d/Genesis/imbuement/shadows/skill_knife_shadow.c
 *
 *  Gives a knife boost to wielder
 *
 *  2010/09/15 Lavellan
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
    ::init_skillboost(lvl, SS_WEP_KNIFE, "knife",
        "It is pulsing with the " + POWER_DESC[lvl] + " aura of a spider.");
    set_add_item_array( ({"blah"}) );
    set_add_item_desc("It's a blah.\n");
} /* init_imbue_shadow */
