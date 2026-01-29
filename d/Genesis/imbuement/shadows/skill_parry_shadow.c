/*
 *  /d/Genesis/imbuement/shadows/skill_parry_shadow.c
 *
 *  Gives a parry boost to wielder
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
    ::init_skillboost(lvl, SS_PARRY, "parry", "You notice "
        + A_POWER_DESC[lvl] + " purple gleam playing off its surface.");

    set_add_item_array( ({ "gleam",
                           "purple gleam",
                           "slight gleam",
                           "pronounced gleam",
                           "intense gleam",
                           "slight purple gleam",
                           "pronounced purple gleam",
                           "intense purple gleam" }) );

    set_add_item_desc("As light is reflected off of this object, the"
      + " gleam is a decidedly purple colour. How strange!\n");

    set_nullstone_type("deft");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The purple gleam fades from the surface of the "
      + shadow_who->short() + " and disappears.\n";
} /* dispel_msg_hook */

