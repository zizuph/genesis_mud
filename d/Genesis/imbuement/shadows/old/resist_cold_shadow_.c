/*
 *  /d/Genesis/imbuement/shadows/resist_cold_shadow.c
 *
 *  Gives cold resistance to wielder
 *
 *  2010/09/09 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"
#include <stdproperties.h> 

inherit SHADOW_DIR + "resistance_base";

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
    ::init_resistance(lvl, MAGIC_I_RES_COLD, "cold",
        "It looks strange. You see a blah.",
        "you feel warmer.", "you feel colder.");
    set_add_item_array( ({"blah"}) );
    set_add_item_desc("It's a blah.\n");
} /* init_imbue_shadow */
