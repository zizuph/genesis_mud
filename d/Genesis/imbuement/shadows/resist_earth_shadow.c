/*
 *  /d/Genesis/imbuement/shadows/resist_earth_shadow.c
 *
 *  Gives earth resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_EARTH, "earth", "the forces of earth",
        CA_POWER_DESC[lvl] + " feeling of drowsiness comes over you as peer" +
        " at it.");

    set_add_item_array( ({ "drowsiness",
                           "feeling",
                           "feeling of drowsiness",
                           "drowsy feeling",
                           "slight feeling",
                           "pronounced feeling",
                           "intense feeling",
                           "slight feeling of drowsiness",
                           "pronounced feeling of drowsiness",
                           "intense feeling of drowsiness" }) );

    set_add_item_desc("Yawn ... hmm ... what's this? You seem to be"
      + " fighting sleep even looking at this object. How ... yawn ..."
      + " uncanny!\n");

    set_nullstone_type("river");
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
        + " and the drowsiness leaves your mind.\n";
} /* dispel_msg_hook */