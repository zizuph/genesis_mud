/*
 *  /d/Genesis/imbuement/shadows/resist_cold_shadow.c
 *
 *  Gives cold resistance to wielder
 *
 *  2010/09/09 Lavellan (descriptions by Gorboth)
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
    ::init_resistance(lvl, MAGIC_I_RES_COLD, "cold", "the effects of cold",
        "You get " + POWER_DESC[lvl] + " goosebumps being around this" +
        " object.");

    set_add_item_array( ({ "goosebump",
                           "goosebumps",
                           "slight goosebumps",
                           "pronounced goosebumps",
                           "intense goosebumps", }) );

    set_add_item_desc("Whoa ... what a strange feeling. This object"
      + " has the same effect as a hot summer breeze on wet skin - it"
      + " raises goosebumps!\n");

    set_nullstone_type("wool");
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
        + " and the goosebumps on your skin disappear.\n";
} /* dispel_msg_hook */