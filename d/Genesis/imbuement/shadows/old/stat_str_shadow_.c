/*
 *  /d/Genesis/imbuement/shadows/stat_boost_str.c
 *
 *  Gives a strength boost to wielder
 *
 *  2010/08/31 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "stat_boost_base";

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
    ::init_statboost(lvl, SS_STR, "It looks strange. You see a blah.",
        "you feel stronger.", "you feel weaker.");
    set_add_item_array( ({"blah"}) );
    set_add_item_desc("It's a blah.\n");
} /* init_imbue_shadow */
