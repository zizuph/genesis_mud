/*
 *  /d/Genesis/imbuement/shadows/water_damage_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect causes water damage a % of the time the
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
         + " extra water damage (" + POWER_LEVEL_DESC[Power_Level]
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

    set_resistance_type(MAGIC_I_RES_WATER);
    set_hit_descs( ({ "redden the skin on", "blanch the skin on",
                      "sear the skin on", "broil the skin on",
                      "hard-boil the skin on" }) );
    set_damage_msgs( ({ "a shrill hiss sounds out as jets of hot steam"
                      + " erupt from",
                        "steam" }) );
    set_add_item_array(   ({ "sound", "hiss", "hissing",
                             "hissing sound",
                             "faint hiss",
                             "faint hissing",
                             "faint sound",
                             "faint hissing sound",
                             "pronounced hiss",
                             "pronounced hissing",
                             "pronounced sound",
                             "pronounced hissing sound",
                             "intense hiss",
                             "intense hissing",
                             "intense sound",
                             "intense hissing sound", }) );
    set_add_item_desc("Hissing ... coming from a object? There is"
        + " something most unnerving about this sound.\n");
    set_nullstone_type("blue");
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
    return capitalize(LANG_ADDART(POWER_DESC[Power_Level])) + " hissing "
        + "sound issues from the item.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The hissing sound issuing from the "
      + shadow_who->short() + " dissipates and is gone.\n";
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
      + POWER_LEVEL_DESC[Power_Level] + "-intensity water to"
      + " damage an opponent in combat!";
} /* query_imbue_info */
