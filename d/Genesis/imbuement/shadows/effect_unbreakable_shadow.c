/*
 *  /d/Genesis/imbuement/shadows/unbreakable_shadow.c
 *
 *  This shadow makes an item resistant to damage or unbreakable.
 *
 *  2010/09/11 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define CHANCE           2
#define MOD              3
//#define MOD              5

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public int               set_dull(int x);
public int               set_corroded(int x);
public int               set_condition (int x);
public varargs void      remove_broken(int x);
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
    
    set_add_item_array( ({ "gleam",
                           "mithril",
                           "mithril gleam",
                           "gleam of mithril",
                           "intense gleam",
                           "intense gleam of mithril",
                           "pronounced gleam",
                           "pronounced gleam of mithril",
                           "slight gleam",
                           "slight gleam of mithril", }) );

    set_add_item_desc("The gleam surrounding this object is somewhat"
      + " confusing. The object does not so much appear to be made of"
      + " mithril in physical form so much as in spiritual form. Your"
      + " mind reels slightly at this distinction.\n");

    set_nullstone_type("iron");
    switch (lvl)
    {
    case 1:
        shadow_who->set_likely_dull(shadow_who->query_likely_dull() - MOD);
        shadow_who->set_likely_corr(shadow_who->query_likely_corr() - MOD);
        shadow_who->set_likely_cond(shadow_who->query_likely_cond() - MOD);
        shadow_who->set_likely_break(shadow_who->query_likely_break() - MOD);
        break;
    case 2:
        shadow_who->set_likely_dull(shadow_who->query_likely_dull() - MOD);
        shadow_who->set_likely_corr(shadow_who->query_likely_corr() - MOD);
        shadow_who->set_likely_cond(shadow_who->query_likely_cond() - MOD);
        shadow_who->set_likely_break(-50000000);
        break;
    case 3:
        shadow_who->set_likely_dull(-50000000);
        shadow_who->set_likely_corr(-50000000);
        shadow_who->set_likely_cond(-50000000);
        shadow_who->set_likely_break(-50000000);
        break;
    }
} /* init_imbue_shadow */


/*
 * Function name:        set_dull
 * Description  :        Ignore or give chance to ignore dull
 * Returns      :        int - New dull amount
 */
public int
set_dull(int x)
{
    if (Power_Level == 3)
        return shadow_who->query_dull();

    if (!random(CHANCE - 1))
        return shadow_who->query_dull();
    else
        return shadow_who->set_dull(x);
} /* set_dull */


/*
 * Function name:        set_corroded
 * Description  :        Ignore or give chance to ignore corrosion
 * Returns      :        int - New corr amount
 */
public int
set_corroded(int x)
{
    if (Power_Level == 3)
        return shadow_who->query_corroded();

    if (!random(CHANCE - 1))
        return shadow_who->query_corroded();
    else
        return shadow_who->set_corroded(x);
} /* set_corroded */


/*
 * Function name:        set_condition
 * Description  :        Ignore or give chance to ignore damage
 * Returns      :        int - New cond amount
 */
public int
set_condition(int x)
{
    if (Power_Level == 3)
        return shadow_who->query_condition();

    if (!random(CHANCE - 1))
        return shadow_who->query_condition();
    else
        return shadow_who->set_condition(x);
} /* set_condition */



/*
 * Function name:        remove_broken
 * Description  :        Ignore or give chance to ignore breaking
 * Returns      :        int - New dull amount
 */
varargs void
remove_broken(int x)
{
    if (calling_function() == "item_expiration_break") 
        shadow_who->remove_broken(x);

    if (Power_Level >= 2)
        return;

    if (!random(CHANCE - 1))
        return;
    else
        shadow_who->remove_broken(x);
} /* remove_broken */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "A powerful enchantment has been bestowed on this item, giving"
        + " it a " + POWER_LEVEL_DESC[Power_Level] + " level of increased"
        + " structural durability!";
/*     switch (Power_Level)
    {
    case 1:
        return "This item has been imbued with magic that makes it more"
            + " resilient.";
    case 2:
        return "This item has been imbued with magic that makes it much"
            + " more resilient.";
    case 3:
        return "This item has been imbued with powerful magic; it is"
            + " immune to damage and resistant to dulling.";
    }
    return "Hmm!"; */
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

    switch (Power_Level)
    {
    case 1:
        str += "This item has been given an imbuement that reduces the "
            + "dull/corrode/break likeliness by " + MOD + " and gives a 1 in "
            + CHANCE + " chance of ignoring these effects.\n";
        break;
    case 2:
        str += "This item has been given an imbuement that reduces the "
            + "dull/corrode likeliness by " + MOD + " and gives a 1 in "
            + CHANCE + " chance of ignoring these effects. It is unbreakable.\n";
        break;
    case 3:
        str += "This item has been given an imbuement that makes it"
            + " immune to dulling, corrosion, and breaking.\n";
        break;
    }
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
    return "The mithril coating on the " + shadow_who->short() + " seems to"
        + " melt away, leaving the surface looking mundane and ordinary.\n";
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
    return CA_POWER_DESC[Power_Level] + " gleam of mithril seems to coat this"
        + " object.";
}
