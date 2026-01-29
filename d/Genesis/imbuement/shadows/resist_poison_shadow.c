/*
 *  /d/Genesis/imbuement/shadows/resist_poison_shadow.c
 *
 *  Gives poison resistance to wielder
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
    ::init_resistance(lvl, MAGIC_I_RES_POISON, "poison", "poison",
        "Being near this object gives you " + A_POWER_DESC[lvl] +
        " urge to sneeze.");

    set_add_item_array( ({ "sneeze",
                           "urge",
                           "urge to sneeze",
                           "slight urge",
                           "pronounced urge",
                           "intense urge",
                           "slight urge to sneeze",
                           "pronounced urge to sneeze",
                           "intense urge to sneeze" }) );

    set_add_item_desc("Ack! What is this? You ... ahhh ... feel ..."
      + " a most definite ... ahhh ... ahhh-CHOO! This is just simply"
      + " bizarre.\n");

    set_nullstone_type("sweat");
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
        + " and the urge to sneeze disappears.\n";
} /* dispel_msg_hook */