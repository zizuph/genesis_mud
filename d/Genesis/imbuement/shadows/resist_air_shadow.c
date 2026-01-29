/*
 *  /d/Genesis/imbuement/shadows/resist_air_shadow.c
 *
 *  Gives air resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_AIR, "air", "the powers of the air",
        "The presence of this object causes " + POWER_DESC[lvl] +
        " ringing in your ears.");

    set_add_item_array( ({ "ringing",
                           "ring",
                           "ringing in my ears",
                           "slight ringing",
                           "slight ringing in my ears",
                           "pronounced ringing",
                           "pronounced ringing in my ears",
                           "intense ringing",
                           "intense ringing in my ears" }) );

    set_add_item_desc("Arrgh. Being around this object is becoming"
      + " more unpleasant by the minute. The ringing in your ears"
      + " almost gives you a headache!\n");

    set_nullstone_type("tarp");
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
        + " and the ringing in your ears ceases.\n";
} /* dispel_msg_hook */