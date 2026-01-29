/*
 *  /d/Genesis/imbuement/shadows/acid_damage_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect causes acid damage 10% of the time the weapon
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

/* Global Variables */
public int               Power_Level = 1;


/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
varargs public mixed     long(string str, object for_obj);
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

    str += "This weapon has been given a random magic mod that does"
         + " extra acid damage (" + POWER_LEVEL_DESC[Power_Level]
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

    set_resistance_type(MAGIC_I_RES_ACID);
    set_hit_descs( ({ "reddens the flesh of", "stings the flesh of",
                      "scalds the flesh of", "melts the flesh of",
                      "ravages the flesh of" }) );
    set_damage_msgs( ({ "a mist of black acid sprays from",
                        "acid cloud" }) );
    set_add_item_array(   ({ "acid", "acid sheen", "faint acid sheen",
                             "faint sheen", "pronounced acid sheen", 
                             "pronounced sheen", "intense acid sheen",
                             "intense sheen", "sheen" }) );
    set_add_item_desc(
        "There is something very strange about this weapon. Acid is"
      + " glistening along its length, as if held there by some magic"
      + " force.\n");
} /* init_imbue_shadow */


/*
 * Function name: long
 * Description  : Describe the object or one pseudo item in it. This
 *                resolves possible VBFC.
 *                *** NOTE! This lfun does not do a write() !! ***
 * Arguments    : string str - the pseudo-item to describe. This is an
 *                             item added with add_item. If this is 0, it
 *                             will return the description of the whole
 *                             object.
 *                object for_obj - the object trying to get the long.
 * Returns      : string - the description of the object or pseudo-item.
 *
 * We mask this to create a modified long description for an imbued item.
 */
varargs public mixed
long(string str, object for_obj)
{
    if (stringp(str))
    {
        return shadow_who->long(str, for_obj);
    }

    return shadow_who->long(str, for_obj) + "It glistens with "
      + LANG_ADDART(POWER_DESC[Power_Level]) + " acid sheen.\n";
} /* long */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The " + POWER_DESC[Power_Level] + " acid sheen which covers"
      + " the " + shadow_who->short() + " evaporates, and is gone.\n";
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
      + POWER_LEVEL_DESC[Power_Level] + "-intensity acid to"
      + " damage an opponent in combat!";
} /* query_imbue_info */