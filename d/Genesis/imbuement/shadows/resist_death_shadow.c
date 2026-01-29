/*
 *  /d/Genesis/imbuement/shadows/resist_death_shadow.c
 *
 *  Gives death resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_DEATH, "death", "the powers of death",
        "You get " + A_POWER_DESC[lvl] + " feeling of nausea as you stare" +
        " at it.");

    set_add_item_array( ({ "nausea",
                           "feeling",
                           "feeling of nausea",
                           "nauseated feeling",
                           "slight feeling",
                           "pronounced feeling",
                           "intense feeling",
                           "slight feeling of nausea",
                           "pronounced feeling of nausea",
                           "intense feeling of nausea" }) );

    set_add_item_desc("Ugh ... the feeling you are getting by being"
      + " around this object is pretty horrible. It literally feels like"
      + " it is making you sick. What could be doing this?\n");

    set_nullstone_type("lars");
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
        + " and the nauseated feeling instantly leaves your body.\n";
} /* dispel_msg_hook */