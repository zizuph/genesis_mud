/*
 *  /d/Genesis/imbuement/shadows/effect_healing_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect heals the user every so often
 *
 *  2010/09/13 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

#include <macros.h>

/* Definitions */
#define HEAL_FAIL_CHANCE    ({ 50, 50, 50 })
#define HEAL_PERCENT        ({ 3, 6, 12 })
#define HEAL_INTERVAL       60.0

/* Global Variables */
public int               Heal_Alarm;

/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
public void              heal();
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

    str += "This item has been given a random magic mod that has a 50%"
        + " chance to heal the user for " + HEAL_PERCENT[query_imbuement_power_level()-1]
        + "% every minute.\n";
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

    set_add_item_array(   ({ "feeling",
                             "security",
                             "feeling of security",
                             "slight feeling",
                             "slight feeling of security",
                             "pronounced feeling",
                             "pronounced feeling of security",
                             "intense feeling",
                             "intense feeling of security" }) );

    set_add_item_desc(
        "This is not something that can be seen, but merely felt."
      + " Nonetheless, there is something uncanny about this object!\n");

    set_nullstone_type("balm");

    setuid();
    seteuid(getuid());
    Heal_Alarm = set_alarm(HEAL_INTERVAL, HEAL_INTERVAL, heal);
} /* init_imbue_shadow */

/*
 * Function:    calculate_heal_imbuement_percentage
 * Description: Called for every heal invocation to determine how much this
 *              imbuement should heal. It will take into account stacking
 */
public float
calculate_heal_imbuement_percentage()
{
    // Each imbuement has a base percentage that it is supposed to boost
    float base_percent = itof(HEAL_PERCENT[query_imbuement_power_level() - 1]);

    // We order all the same imbuements active on the person, ordered by power level
    object * all_same_imbue_items = find_all_same_imbuement_items();

    // Now find the position of the item in this array
    float position = itof(member_array(shadow_who, all_same_imbue_items));
    
    if (position < 0.0)
    {
        // This should never happen, but in case it does, we just return the base
        // percentage.
        return base_percent;
    }

    // Now, we multiply by pow(0.60, position) to get the real percentage
    float modified_percent = base_percent * pow(0.60, position);
//    send_debug_message("healing_imbue", 
//                       sprintf("Position %d yields %f percentage from base %f percentage.", 
//                               ftoi(position), modified_percent, base_percent));

    return modified_percent;
}

/*
 * Function name: heal
 * Description:   heal the wielder (perhaps)
 */
public void
heal()
{
    object liv = shadow_who->query_wielded();
    string t;
    int amt;

    if (!liv)
        liv = shadow_who->query_worn();

    if (!liv)
        return;

    if (liv->query_hp() >= liv->query_max_hp())
    {
        return;
    }

    if (random(100) < HEAL_FAIL_CHANCE[query_imbuement_power_level()-1])
    {
        return;
    }

    if (shadow_who->query_wielded())
    {
        if (sizeof(shadow_who->query_slots()) > 1)
            t = "hands tingle";
        else if (shadow_who->query_slots()[0] == 1024)
            t = "left hand tingles";
        else
            t = "right hand tingles";
        liv->catch_tell("Your " + t + ", and you feel healthier!\n");
    }
    else
        liv->catch_tell("A tingle goes through your body, and you feel"
            + " healthier!\n");
    amt = ftoi(itof(liv->query_max_hp()) * calculate_heal_imbuement_percentage() / 100.0);
    liv->heal_hp(amt);
} /* heal */

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
    return CA_POWER_DESC[query_imbuement_power_level()] + " feeling of"
        + " security emanates from it.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The feeling of security emanating from the "
      + shadow_who->short() + " fades, and then is gone.\n";
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
    return "This item has been imbued with a " + 
      POWER_LEVEL_DESC[query_imbuement_power_level()] + "-level enchantment which"
      + " will heal the user at regular intervals!";
} /* query_imbue_info */
