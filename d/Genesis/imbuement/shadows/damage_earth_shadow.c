/*
 *  /d/Genesis/imbuement/shadows/damage_earth_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect causes earth damage 10% of the time the weapon
 *  strikes.
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
         + " extra earth damage (" + POWER_LEVEL_DESC[Power_Level]
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

    set_resistance_type(MAGIC_I_RES_DEATH);
    set_hit_descs( ({ 
        "thus, with unnatural force, it thunks into",
        "thus, with unnatural force, it bashes into",
        "thus, with unnatural force, it careens into",
        "thus, with unnatural force, it crunches into",
        "thus, with unnatural force, it plows into", }) );
    set_damage_msgs( ({ "The colour and balance seems to suddenly shift in",
                        "object's weight" }) );
    set_add_item_array(   ({ "fluctuation",
                             "fluctuation in the object's colour",
                             "faint fluctuation",
                             "faint fluctuation in the object's colour",
                             "pronounced fluctuation",
                             "pronounced fluctuation in the object's colour",
                             "intense fluctuation",
                             "intense fluctuation in the object's colour",
                             "colour",
                             "object colour",
                             "object's colour",
                             "different material",
                             "fluctuations",
                             "colour fluctuation",
                             "colour fluctuations", }) );
    set_add_item_desc(
        "The nature of this object is somehow magically shifting. At"
      + " one moment, it will appear normal, and then without warning"
      + " shift colour and texture as if it were momentarily made of"
      + " an entirely different material!\n");
    set_nullstone_type("sink");
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
      + " fluctuation in the object's colour seems to be occuring.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The colour fluctuations in the " + shadow_who->short() 
      + " are no longer noticable.\n";
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
      + POWER_LEVEL_DESC[Power_Level] + "-intensity earth magic to"
      + " damage an opponent in combat!";
} /* query_imbue_info */
