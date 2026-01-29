/*
 *  /d/Genesis/imbuement/shadows/stat_str_shadow.c
 *
 *  Gives a strength boost to wielder
 *
 *  2010/08/31 Lavellan (descriptions by Gorboth)
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
    ::init_statboost(lvl, SS_STR, "musk",
        "a strange sensation comes over you, and your possessions feel a bit"
        + " lighter.", "your possessions suddenly feel a bit heavier.");

    set_add_item_array( ({ "musk",
                           "smell",
                           "smell of musk",
                           "slight smell",
                           "pronounced smell",
                           "intense smell",
                           "slight smell of musk",
                           "pronounced smell of musk",
                           "intense smell of musk" }) );

    set_add_item_desc("Sniff ... sniff ... What is this strange smell?"
      + " Musk? Coming from an object like this? What could possibly"
      + " explain such a thing?\n");

    set_nullstone_type("ogre");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The smell of musk coming from the " + shadow_who->short()
        + " is no longer noticable.\n";
} /* dispel_msg_hook */

