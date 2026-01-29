/*
 *  /d/Genesis/imbuement/shadows/damage_air_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect causes air damage a % of the time the
 *  weapon strikes.
 *
 *  Created November 2009 by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "elemental_damage_shadow";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
public string            dispel_msg_hook();
public string            query_imbue_info();


/*
 * Function name: stat_object
 * Description:   This function is called when a wizard wants to get more 
 *                information about an object.
 * Returns:       str - The string to write..
 */
public string
stat_object()
{
    string  str = shadow_who->stat_object();

    str += "This item has been given a random magic mod that does"
         + " extra air-based damage (" + POWER_LEVEL_DESC[Power_Level]
         + " amount) roughly 10% of the time.\n";
    return str;
} /* stat_object */


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
    ::init_imbue_shadow(lvl);

    Power_Level = lvl;

    set_resistance_type(MAGIC_I_RES_AIR);
    set_hit_descs( ({ "ruffle the skin on", "buffet the skin on",
                      "whip the skin on", "severely lash the skin on",
                      "rip the skin off of" }) );
    set_damage_msgs( ({ "with a piercing whistle, deadly bolts of air"
                      + " shoot from",
                        "wind attack" }) );
    set_add_item_array(   ({ "air", "disturbance",
                             "disturbance in the air",
                             "unmistakable disturbance",
                             "unmistakable disturbance in the air",
                             "ether" }) );
    set_add_item_desc(
        "There is an unmistakable disturbance in the air surrounding this"
      + " object. It is almost as if the very ether is being agitated!\n");
    set_nullstone_type("blow");
} /* init_imbue_shadow */

/*
 * Function:    query_imbued_indication
 * Description: This is the custom message that gets displayed on an imbued
 *              item to help identify what the particular imbuement is on
 *              the item. It is usually displayed as a part of the "long"
 *              description of the item when examined.
 *              Each imbuement base class should customize this.
 * Returns:     A string that should be displayed to the user when examining
 *              an imbued item. A newline will automatically be added at the
 *              end of the long description.
 */
public string
query_imbued_indication()
{
    return capitalize(LANG_ADDART(POWER_DESC[Power_Level]))
      + " disturbance in the air surrounding the object catches your"
      + " attention.";
}


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The air surrounding the " + shadow_who->short() + " shimmers"
      + " violently, and then is suddenly at peace.\n";
} /* dispel_msg_hook */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "This item has been imbued with elemental magic that causes "
      + POWER_LEVEL_DESC[Power_Level] + "-intensity air-bolts to"
      + " damage an opponent in combat!";
} /* query_imbue_info */
