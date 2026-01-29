/*
 *  /d/Genesis/imbuement/shadows/stat_int_shadow.c
 *
 *  Gives a intelligence boost to wielder
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
    ::init_statboost(lvl, SS_INT, "lavender",
        "you feel a rush flow through your mind, and things make a bit more"
        +" sense all of a sudden.",
        "you feel a powerful loss of energy within your mind.");

    set_add_item_array( ({ "lavender",
                           "smell",
                           "smell of lavender",
                           "slight smell",
                           "pronounced smell",
                           "intense smell",
                           "slight smell of lavender",
                           "pronounced smell of lavender",
                           "intense smell of lavender" }) );

    set_add_item_desc("Sniff ... sniff ... What is this strange smell?"
      + " Lavender? Coming from an object like this? What could possibly"
      + " explain such a thing?\n");

    set_nullstone_type("gnome");
} /* init_imbue_shadow */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The smell of lavender coming from the " + shadow_who->short()
        + " is no longer noticable.\n";
} /* dispel_msg_hook */


