/*
 *  /d/Genesis/imbuement/shadows/resist_life_shadow.c
 *
 *  Gives life resistance to wielder
 *
 *  2010/09/17 Lavellan (descriptions by Gorboth)
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
    ::init_resistance(lvl, MAGIC_I_RES_LIFE, "life", "the powers of life",
        "It gives you "  + A_POWER_DESC[lvl] + " feeling of unease.");

    set_add_item_array( ({ "unease",
                           "feeling",
                           "feeling of unease",
                           "uneasy feeling",
                           "slight feeling",
                           "pronounced feeling",
                           "intense feeling",
                           "slight feeling of unease",
                           "pronounced feeling of unease",
                           "intense feeling of unease" }) );

    set_add_item_desc("You aren't sure why, but there is an aspect"
      + " to this object that puts you ill-at-ease - some magic within,"
      + " perhaps, that does not sit well with your soul.\n");

    set_nullstone_type("mummy");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "There is a flash of energy from the " + shadow_who->short()
        + " and the uneasy feeling leaves you.\n";
} /* dispel_msg_hook */