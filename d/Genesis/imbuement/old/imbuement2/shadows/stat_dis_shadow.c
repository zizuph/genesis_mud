/*
 *  /d/Genesis/imbuement/shadows/stat_discipline_shadow.c
 *
 *  Gives a discipline boost to wielder
 *
 *  2010/09/15 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "stat_base";

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
    ::init_statboost(lvl, SS_DIS, "vanilla",
        "an uncanny feeling of confidence flows through you.",
        "your confidence falters a bit.");
    set_add_item_array( ({"blah"}) );
    set_add_item_desc("It's a blah.\n");
} /* init_imbue_shadow */
