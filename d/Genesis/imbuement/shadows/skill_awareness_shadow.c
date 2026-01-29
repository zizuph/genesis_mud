/*
 *  /d/Genesis/imbuement/shadows/skill_awareness_shadow.c
 *
 *  Gives an awareness boost to wielder
 *
 *  2010/09/15 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "skill_base";

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
    ::init_skillboost(lvl, SS_AWARENESS, "awareness",
        CA_POWER_DESC[lvl] + " orange glow surrounds its surface.");

    set_add_item_array( ({ "glow",
                           "orange glow",
                           "slight glow",
                           "pronounced glow",
                           "intense glow",
                           "slight orange glow",
                           "pronounced orange glow",
                           "intense orange glow" }) );

    set_add_item_desc("What sort of enchantment is at work here? There is"
      + " an unmistakable orange glow coming from this object!\n");

    set_nullstone_type("eye");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The orange glow surrounding the " + shadow_who->short()
        + " fades and is gone.\n";
} /* dispel_msg_hook */

