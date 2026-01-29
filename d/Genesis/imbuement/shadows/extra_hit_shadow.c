/*
 *  /d/Genesis/imbuement/shadows/extra_hit_shadow.c
 *
 *  This shadow gives extra "hit" to a weapon.
 *
 *  2010/09/09 Lavellan (descriptions by Gorboth)
 *  2022/03/16 Ckrik - scale cap by weapon type and hand slot
 */
#pragma strict_types
#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define BOOST_AMOUNT        ({5, 10, 25})

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public int               query_hit();
public string            query_imbue_info();
public string            stat_object();
public string            dispel_msg_hook();

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
                           "viciousness",
                           "aura of viciousness",
                           "slight aura of viciousness",
                           "pronounced aura of viciousness",
                           "intense aura of viciousness", }) );

    set_add_item_desc("It almost feels like there is an angry spirit"
      + " within this item struggling to get out. How disturbing!\n");

    set_nullstone_type("guide");
} /* init_imbue_shadow */


/*
 * Function name:        query_hit
 * Description  :        Mask the query_hit of the base item
 * Returns      :        int - Hit of base item plus our extra
 */
public int
query_hit()
{
    int orig, boost, cap;
    orig = shadow_who->query_hit();
    boost = BOOST_AMOUNT[Power_Level - 1];

    if (IS_WEAPON_OBJECT(shadow_who))
    {
        if (shadow_who->query_wt() == W_KNIFE)
        {
            cap = 40;
        }
        else
        {
            if (shadow_who->query_hands() == W_BOTH)
            {
                cap = 60;
            }
            else
            {
                cap = 50;
            }
        }
    }
    else
    {
        // unarmed enhancer
        cap = 50;
    }

    if (orig + boost <= cap)
    {
        return orig + boost;
    }
    else
    {
        return cap + (((orig + boost) - cap) / 3);
    }
} /* query_hit */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "This item has been imbued with a "
      + POWER_LEVEL_DESC[Power_Level] + "-level enchantment which increases "
      + "its accuracy!";
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

    str += "This item has been given a random magic mod that gives a "
         + POWER_LEVEL_DESC[Power_Level] + "(" + BOOST_AMOUNT[Power_Level - 1]
         + ") extra \"hit\" to the item. Modified hit="
         + this_object()->query_hit() + ".\n";
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
    return "The aura of viciousness surrounding the " 
        + shadow_who->short() + " fades and is gone.\n";
} /* dispel_msg_hook */

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
    return "It exudes " + A_POWER_DESC[Power_Level] + " aura of viciousness.";
}
