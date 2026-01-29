/*
 *  /d/Genesis/imbuement/shadows/slow_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect slows the enemy using a "poison"
 *
 *  2010/09/13 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <files.h>      //for IS_PLAYER_OBJECT

inherit SHADOW_DIR + "imbuement_shadow";

#include <macros.h>

/* Global Variables */
public int               Poison_Alarm;

/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
public varargs int       did_hit(int aid, string hdesc, int phurt,
                                 object enemy, int dt, int phit, int dam);
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

    str += "This weapon has been given a random magic mod that slows the"
         + " enemy via a \"poison\".\n";
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

    set_add_item_array(   ({ "drone",
                             "sound",
                             "low-pitched sound",
                             "slight drone",
                             "pronounced drone",
                             "intense drone" }) );

    set_add_item_desc(
        "A low-pitched sound issues from this object, causing everything"
      + " around it to vibrate in a strange and disturbing fashion.\n");

    set_nullstone_type("grog");

    setuid();
    seteuid(getuid());
} /* init_imbue_shadow */


/*
 * Function name: did_hit
 * Description:   masked to cause the slowness.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam);
    object sobj;
    object  item_owner = environment(shadow_who);

    if (!objectp(enemy))
    {
        return (rval);
    }
    
    if (!dam)
    {
        return (rval);
    }

    if (sobj = present("_imbue_slow_effect", enemy))
    {
        sobj->restart_slow();
        return (rval);
    }

    sobj = clone_object(SHADOW_DIR + "effect_slow_effect");
    sobj->move(enemy, 1);
    sobj->set_level(Power_Level);
    sobj->start_slow(shadow_who->query_wielded());

    if (IS_PLAYER_OBJECT(item_owner) && IS_PLAYER_OBJECT(enemy))
        IMBUE_LOGGER->log("pvp", sprintf("%s by %s  slow/%s (%d)",
            capitalize(enemy->query_real_name()),
            capitalize(item_owner->query_real_name()),
            shadow_who->short(),
            query_id()));

    return (rval);
} /* did_hit */

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
    return capitalize(LANG_ADDART(POWER_DESC[Power_Level])) + " drone issues"
        + " from this weapon.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The droning sound coming from " + shadow_who->short()
        + " grows more and more faint, eventually subsiding altogether\n";
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
    return "This item has been imbued with "
        + LANG_ADDART(POWER_LEVEL_DESC[Power_Level])
        + "-intensity ability to slow down the enemy of anyone who wields it!";
} /* query_imbue_info */
