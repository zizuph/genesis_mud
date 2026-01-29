/*
 *  /d/Genesis/imbuement/shadows/bane_orc_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect gives a special attack when used against orcs
 *
 *
 *  2010/09/12 Lavellan, based on elemental damage mod by Gorboth
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "bane_base";

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
         + " extra death damage (" + POWER_LEVEL_DESC[Power_Level]
         + " amount) roughly 10% of the time to orcs.\n";
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

    set_races( ({"orc", "uruk", "uruk-hai"}) );
    set_hit_descs( ({ "weakens the flesh of", "sickens the flesh of",
                      "decays the flesh of", "rots the flesh of",
                      "mummifies the flesh of" }) );
    set_damage_msgs( ({ "a sudden pulse of black energy erupts from",
                        "weapon's black touch" }) );
    set_add_item_array(   ({ "odor", "decay", "faint odor",
                             "pronounced odor", "intense odor",
                             "odor of decay", "faint odor of decay",
                             "pronounced odor of decay",
                             "intense odor of decay" }) );
    set_add_item_desc(
        "The smell coming from this weapon is simply dreadful! It is"
      + " as if the weapon had been buried with a dead animal for"
      + " days. Puh!\n");
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

    return shadow_who->long(str, for_obj)
      + capitalize(LANG_ADDART(POWER_DESC[Power_Level]))
      + " odor of decay issues from the weapon.\n";
} /* long */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The " + POWER_DESC[Power_Level] + " odor of decay which issues"
      + " from the " + shadow_who->short() + " is no longer noticable.\n";
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
      + POWER_LEVEL_DESC[Power_Level] + "-intensity damage to"
      + " orcs!";
} /* query_imbue_info */