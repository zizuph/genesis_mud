/*
 *  /d/Genesis/imbuement/shadows/resist_fire_shadow.c
 *
 *  Gives fire resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_FIRE, "fire", "fire",
        CA_POWER_DESC[lvl] + " feeling of calm comes over you in the" +
        " presence of this object.");

    set_add_item_array( ({ "calm",
                           "feeling",
                           "feeling of calm",
                           "calm feeling",
                           "slight feeling",
                           "pronounced feeling",
                           "intense feeling",
                           "slight feeling of calm",
                           "pronounced feeling of calm",
                           "intense feeling of calm" }) );

    set_add_item_desc("The mere presence of this object gives you a"
      + " strange and yet very peaceful and pleasant feeling of"
      + " calm.\n");

    set_nullstone_type("powder");
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
        + " and your feeling of calm dissipates.\n";
} /* dispel_msg_hook */