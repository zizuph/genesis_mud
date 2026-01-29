/*
 *  /d/Genesis/imbuement/shadows/extra_spellpower_shadow.c
 *
 *  This shadow gives extra "spellpower" to an object.
 *
 *  3/16/2022 - Ckrik
 */
#pragma strict_types
#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define BOOST_AMOUNT        ({3, 5, 13})
#define MIN_BOOSTED         ({35, 40, 45})

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public int               query_magic_spellpower();
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
                           "arcana",
                           "aura of arcana",
                           "slight aura of arcana",
                           "pronounced aura of arcana",
                           "intense aura of arcana", }) );

    set_add_item_desc("The mysterious aura emanating from this object " +
      "seems to burst with arcane knowledge.\n");

    set_nullstone_type("enigma");
} /* init_imbue_shadow */


/*
 * Function name:        query_magic_spellpower
 * Description  :        Mask the query_magic_spellpower of the base item
 * Returns      :        int - Spellpower of base item plus our extra
 */
public int
query_magic_spellpower()
{
    int orig, boost, cap, slots;
    orig = shadow_who->query_magic_spellpower();
    boost = BOOST_AMOUNT[Power_Level - 1];

    if (IS_WEAPON_OBJECT(shadow_who))
    {
        slots = shadow_who->query_hands();
    }
    else
    {
        slots = shadow_who->query_slots_setting();
    }

    if (slots == W_BOTH)
    {
        cap = 60;
    }
    else
    {
        cap = 50;
    }

    if (orig + boost <= cap)
    {
        // Since there 
        return max(orig + boost, MIN_BOOSTED[Power_Level - 1]);
    }
    else
    {
        return cap + (((orig + boost) - cap) / 3);
    }

} /* query_magic_spellpower */

/*
 * Function name: query_spellpower_enhancer
 * Description:   Check whether this object can enhance spells.
 */
public int
query_spellpower_enhancer()
{
    return 1;
}

public int*
query_spellpower_elements()
{
    mixed elements = shadow_who->query_spellpower_elements();
    if (elements == 0)
    {
        // Underlying item is a mundane item, so default to
        // everything
        return ({
            SS_ELEMENT_FIRE,
            SS_ELEMENT_WATER,
            SS_ELEMENT_EARTH,
            SS_ELEMENT_AIR,
            SS_ELEMENT_DEATH,
            SS_ELEMENT_LIFE
        });
    }
    return elements;
}

public string get_element_spells()
{
    mixed elements = shadow_who->get_element_spells();
    if (elements == 0)
    {
        return "spells of any element";
    }

    return elements;
}

/*
 * Function name: item_spellpower_desc
 * Description:   String to be shown as part of the item appraisal.
 */
public string
item_spellpower_desc()
{
    string types = get_element_spells();
    
    if (IS_WEAPON_OBJECT(shadow_who))
    {
        return "\nThis weapon can be wielded to enhance " + types + ".\n";
    }
    return "\nThis item can be held to enhance " + types + ".\n";
}

/*
 * Function name: item_spellpower_desc
 * Description:   String to be displayed when an object is statted.
 */
string
stat_object_spellpower()
{
    return "Imbued spell power: " + query_magic_spellpower() + ", elements: " 
        + get_element_spells() + "\n";
}

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
      + "its spell enhancement!";
} /* query_imbue_info */

void 
appraise_object(int num)
{
    shadow_who->appraise_object(num);
    if (!shadow_who->query_spellpower_enhancer())
    {
        write(item_spellpower_desc());
    }
}

/*
 * Function name: stat_object
 * Description:   This function is called when a wizard wants to get more 
 *                information about an object.
 * Returns:       str - The string to write..
 */
public string
stat_object()
{
    string str = shadow_who->stat_object();

    str += "This item has been given a random magic mod that gives a "
         + POWER_LEVEL_DESC[Power_Level] + "(" + BOOST_AMOUNT[Power_Level - 1]
         + ") extra or (" + MIN_BOOSTED[Power_Level - 1] + ") min "
         + "\"spellpower\" to the item. Modified spellpower="
         + this_object()->query_magic_spellpower() + ".\n";
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
    return "The aura of arcana surrounding the " 
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
    return "It exudes " + A_POWER_DESC[Power_Level] + " aura of arcana.";
}
