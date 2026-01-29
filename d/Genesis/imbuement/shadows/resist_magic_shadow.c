/*
 *  /d/Genesis/imbuement/shadows/resist_magic_shadow.c
 *
 *  Gives magic resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_MAGIC, "magic", "all forms of magic",
        CA_POWER_DESC[lvl] + " dull feeling comes over you, looking at" +
        " this object.");

    set_add_item_array( ({ "dullness",
                           "feeling",
                           "dull feeling",
                           "slight feeling",
                           "pronounced feeling",
                           "intense feeling",
                           "slight dull feeling",
                           "pronounced dull feeling",
                           "intense dull feeling" }) );

    set_add_item_desc("The feeling you experience when looking at"
      + " this object is hard to describe. Your energy seems to dim,"
      + " and you feel simply duller than before. What is going on?\n");

    set_nullstone_type("quiet");
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
        + " and the dull feeling in your body goes away.\n";
} /* dispel_msg_hook */