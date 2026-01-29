/*
 *  /d/Genesis/imbuement/shadows/resist_acid_shadow.c
 *
 *  Gives acid resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_ACID, "acid", "acid",
        "Being around this object gives you " + A_POWER_DESC[lvl] +
        " itching sensation.");
    set_add_item_array( ({ "sensation",
                           "itching",
                           "itch",
                           "itching sensation",
                           "slight itching sensation",
                           "pronounced itching sensation",
                           "intense itching sensation", }) );

    set_add_item_desc("Ugh! The urge to itch is undeniable! What"
      + " is it about this object that could cause this?\n");

    set_nullstone_type("salve");
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
        + " and the itching sensation on your skin fades.\n";
} /* dispel_msg_hook */