/*
 *  /d/Genesis/imbuement/shadows/extra_pen_shadow.c
 *
 *  This shadow gives extra "pen" to a weapon.
 *
 *  2010/09/09 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define BOOST_AMOUNT        ({5, 10, 25})

/* Global Variables */
public int               Power_Level = 1;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public int               query_pen();
public string            query_imbue_info();
public string            stat_object();
public string            dispel_msg_hook();
varargs public mixed     long(string str, object for_obj);

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
    
    set_add_item_array( ({ "aura",
                           "slight aura",
                           "pronounced aura",
                           "intense aura",
                           "malevolence",
                           "aura of malevolence",
                           "slight aura of malevolence",
                           "pronounced aura of malevolence",
                           "intense aura of malevolence", }) );

    set_add_item_desc("There is feeling coming from this weapon. It is"
      + " most definitely not a friendly feeling. What strange power"
      + " is this?\n");

    set_nullstone_type("sting");
} /* init_imbue_shadow */


/*
 * Function name:        query_pen
 * Description  :        Mask the query_pen of the base weapon
 * Returns      :        int - Pen of base weapon plus our extra
 */
public int
query_pen()
{
    int orig, boost;
    orig = shadow_who->query_pen();
    boost = BOOST_AMOUNT[Power_Level - 1];
    if (orig + boost <= 60)
        return orig + boost;
    else
    {
        return 60 + (((orig + boost) - 60) / 3);
    }
    //return min(60, shadow_who->query_pen() + BOOST_AMOUNT[Power_Level - 1]);
} /* query_pen */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "This armour has been imbued with a "
      + POWER_LEVEL_DESC[Power_Level] + " enchantment which increases its"
      + " lethality!";
} /* query_imbue_info */


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

    str += "This weapon has been given a random magic mod that gives a "
         + POWER_LEVEL_DESC[Power_Level] + "(" + BOOST_AMOUNT[Power_Level - 1]
         + ") extra \"pen\" to the weapon.\n";
    return str;
} /* stat_object */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The aura of malevolence surrounding the " 
        + POWER_DESC[Power_Level] + " fades and is gone.\n";
} /* dispel_msg_hook */


/*
 * Function name: long
 * Description  : Add our extra info to the long
 * Arguments    : string str - the pseudo-item to describe.
 *                object for_obj - the object trying to get the long.
 * Returns      : string - the description of the object or pseudo-item.
 */
varargs public mixed
long(string str, object for_obj)
{
    if (stringp(str))
    {
        return shadow_who->long(str, for_obj);
    }

    return shadow_who->long(str, for_obj)
      + "It exudes " + A_POWER_DESC[Power_Level] + " aura of malevolence.\n";
} /* long */