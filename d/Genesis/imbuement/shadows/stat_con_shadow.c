/*
 *  /d/Genesis/imbuement/shadows/stat_con_shadow.c
 *
 *  Gives a constitution boost to wielder
 *
 *  2010/09/15 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <ss_types.h> 

inherit SHADOW_DIR + "stat_base";

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
    ::init_statboost(lvl, SS_CON, "alcohol",
        "you feel a sensation pass through every cell in your body. It almost"
        + " feels as if you have become more dense.",
        "the feeling within your body lightens, and you feel less sturdy.");

    set_add_item_array( ({ "alcohol",
                           "smell",
                           "smell of alcohol",
                           "slight smell",
                           "pronounced smell",
                           "intense smell",
                           "slight smell of alcohol",
                           "pronounced smell of alcohol",
                           "intense smell of alcohol" }) );

    set_add_item_desc("Sniff ... sniff ... What is this strange smell?"
      + " Alcohol? Coming from an object like this? What could possibly"
      + " explain such a thing?\n");

    set_nullstone_type("dwarf");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The smell of alcohol coming from the " + shadow_who->short()
        + " is no longer noticable.\n";
} /* dispel_msg_hook */

