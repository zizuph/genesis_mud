/*
 *  /d/Genesis/imbuement/shadows/resist_water_shadow.c
 *
 *  Gives water resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_WATER, "water", "water",
        "For some odd reason, this object gives you " + A_POWER_DESC[lvl] +
        " tickle in your throat.");

    set_add_item_array( ({ "throat",
                           "tickle",
                           "tickle in your throat",
                           "slight tickle",
                           "pronounced tickle",
                           "intense tickle",
                           "slight tickle in your throat",
                           "pronounced tickle in your throat",
                           "intense tickle in your throat" }) );

    set_add_item_desc("Eccch ... what is this ... tickle in your throat? It" +
        " is rather annoying, and utterly bizarre!\n");

    set_nullstone_type("duck");
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
        + " and the tickle in your throat is gone.\n";
} /* dispel_msg_hook */