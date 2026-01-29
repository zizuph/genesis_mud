/*
 *  /d/Genesis/imbuement/shadows/skill_spellcraft_shadow.c
 *
 *  Gives a spellcraft boost to wielder
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
    ::init_skillboost(lvl, SS_SPELLCRAFT, "spellcraft",
        CA_POWER_DESC[lvl] + " aura of crimson energy surrounds this object.");

    set_add_item_array( ({ "aura",
                           "aura of crimson energy",
                           "slight aura",
                           "pronounced aura",
                           "intense aura",
                           "aura of energy",
                           "slight aura of energy",
                           "pronounced aura of energy",
                           "intense aura of energy",
                           "slight aura of crimson energy",
                           "pronounced aura of crimson energy",
                           "intense aura of crimson energy",
                           "energy",
                           "crimson energy" }) );

    set_add_item_desc("What sort of enchantment is at work here? There is"
      + " an unmistakable aura of crimson energy coming from this object!\n");

    set_nullstone_type("lode");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The aura of crimson energy surrounding the " + shadow_who->short()
        + " pulses brightly, and is gone.\n";
} /* dispel_msg_hook */

