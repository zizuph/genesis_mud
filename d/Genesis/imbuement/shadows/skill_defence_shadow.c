/*
 *  /d/Genesis/imbuement/shadows/skill_defence_shadow.c
 *
 *  Gives a defence boost to wielder
 *
 *  2010/09/09 Lavellan (descriptions by Gorboth)
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
    ::init_skillboost(lvl, SS_DEFENCE, "defence", 
        "It is surrounded by " + POWER_DESC[lvl] + "ly swirling bands of"
        + " yellow energy.");

    set_add_item_array( ({ "swirling bands of yellow energy",
                           "band",
                           "bands",
                           "band of energy",
                           "bands of energy",
                           "energy",
                           "yellow energy",
                           "band of yellow energy",
                           "bands of yellow energy",
                           "swirling band",
                           "swirling bands",
                           "swirling band of energy",
                           "swirling bands of energy",
                           "slightly swirling band",
                           "slightly swirling bands",
                           "slightly swirling band of energy",
                           "slightly swirling bands of energy",
                           "pronouncedly swirling band",
                           "pronouncedly swirling bands",
                           "pronouncedly swirling band of energy",
                           "pronouncedly swirling bands of energy",
                           "intensely swirling band",
                           "intensely swirling bands",
                           "intensely swirling band of energy",
                           "intensely swirling bands of energy",
                           "slightly swirling bands of yellow energy",
                           "pronouncedly swirling bands of yellow energy",
                           "intensely swirling bands of yellow energy" }) );

    set_add_item_desc("Yellow bands of energy are swirling in the air"
      + " around this object. There appears to be some sort of enchantment"
      + " at work!\n");

    set_nullstone_type("shield");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The swirling bands of yellow energy surrounding the "
        + shadow_who->short() + " flash and disappear.\n";
} /* dispel_msg_hook */

