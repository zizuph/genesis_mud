/*
 *  /d/Genesis/imbuement/shadows/resist_electricity_shadow.c
 *
 *  Gives electricity resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_ELECTRICITY, "electricity",
        "electricity", CA_POWER_DESC[lvl] + " hair-raising sensation grips" +
        " you as you examine this object.");

    set_add_item_array( ({ 
                           "sensation",
                           "hair raising sensation",
                           "hair-raising sensation",
                           "slight sensation",
                           "pronounced sensation",
                           "intense sensation",
                           "slight hair-raising sensation",
                           "slight hair raising sensation",
                           "pronounced hair-raising sensation",
                           "pronounced hair raising sensation",
                           "intense hair-raising sensation",
                           "intense hair raising sensation" }) );

    set_add_item_desc("Whoa ... the hairs all over your body are somehow"
      + " responding to the presence of this object. What could this"
      + " mean?\n");

    set_nullstone_type("rubber");
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
        + " and the hairs on your body stop standing on end.\n";
} /* dispel_msg_hook */