/*
 *  /d/Genesis/imbuement/shadows/haste_shadow.c
 *
 *  Gives haste to wielder
 *
 *  2010/09/09 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

#include <macros.h>
#include <files.h>      //for IS_PLAYER_OBJECT

/* Definitions */
#define BOOST_AMOUNT        ({25, 50, 100})

/* Global Variables */
public int               Boost = 0;
public object            oldwf;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield(int num);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear(int num);
public string            stat_object();
public string            dispel_msg_hook();
public string            query_imbue_info();
static void              tell_owner(object owner, string msg);
public int               calculate_boost();
public void              remove_boost();
public void              add_boost(int factor = 0);
public void              reset_all_boosts();

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

    set_add_item_array( ({ "whine",
                           "slight whine",
                           "pronounced whine",
                           "intense whine" }) );

    set_add_item_desc("The noise coming from this " + shadow_who->short()
      + " is undeniable. It sounds like a 10 pound mosquito with an"
      + " attitude. What could be causing it?\n");

    set_nullstone_type("mercury");

    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());
} /* init_imbue_shadow */


/*
 * Function name:        wield
 * Description  :        Show message and add quickness when wielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
wield(object obj)
{
    mixed res = oldwf->wield(obj);
    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, do_wield);
    }
    return res;
} /* wield */


/*
 * Function name:        unwield
 * Description  :        Show message and remove quickness when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    mixed res = oldwf->unwield(obj);
    object wielder = shadow_who->query_wielded();

    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &tell_owner(wielder, "As you release the " +
            shadow_who->short() + ", your pulse slows, and you feel your" +
            " energy level returning to normal.\n"));
        remove_boost();
        set_alarm(0.0, 0.0, &reset_all_boosts());
        if (IS_PLAYER_OBJECT(wielder))
            IMBUE_LOGGER->log("haste", sprintf("%s  -%d to %d  haste/%s (%d)",
                capitalize(wielder->query_real_name()),
                BOOST_AMOUNT[query_imbuement_power_level()-1],
                wielder->query_prop(LIVE_I_QUICKNESS),
                shadow_who->short(),
                query_id()));
    }
    return res;
} /* unwield */


/*
 * Function name:        do_wield
 * Description  :        The actual message display and quickness modification.
 */
public void
do_wield(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wield(num);
        return;
    }
    object wielder = shadow_who->query_wielded();

    write("As you wield the " + shadow_who->short() +
        ", your heart begins to race, and you feel energy bursting from" +
        " your every pore.\n");
    reset_all_boosts();
    if (IS_PLAYER_OBJECT(wielder))
    IMBUE_LOGGER->log("haste", sprintf("%s  +%d to %d  haste/%s (%d)",
        capitalize(wielder->query_real_name()),
        BOOST_AMOUNT[query_imbuement_power_level()-1],
        wielder->query_prop(LIVE_I_QUICKNESS),
        shadow_who->short(),
        query_id()));
} /* do_wield */


/*
 * Function name:        wear
 * Description  :        Show message and add quickness when wearing
 *                       the armour.
 * Returns      :        int - It could be worn or not
 */
public mixed
wear(object obj)
{
    mixed res = oldwf->wear(obj);
    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, do_wear);
    }
    return res;
} /* wear */


/*
 * Function name:        remove
 * Description  :        Show message and remove quickness when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    mixed res = oldwf->remove(obj);
    object wearer = shadow_who->query_worn();

    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &tell_owner(wearer, "As you remove the " +
            shadow_who->short() + ", your pulse slows, and you feel your" +
            " energy level returning to normal.\n"));
        remove_boost();
        set_alarm(0.0, 0.0, &reset_all_boosts());
        if (IS_PLAYER_OBJECT(wearer))
            IMBUE_LOGGER->log("haste", sprintf("%s  -%d to %d  haste/%s (%d)",
                capitalize(wearer->query_real_name()),
                BOOST_AMOUNT[query_imbuement_power_level()-1],
                wearer->query_prop(LIVE_I_QUICKNESS),
                shadow_who->short(),
                query_id()));
    }
    return res;
} /* remove */


/*
 * Function name:        do_wear
 * Description  :        The actual message display and quickness modification.
 */
public void
do_wear(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wear(num);
        return;
    }
    object wearer = shadow_who->query_worn();

    write("As you wear the " + shadow_who->short() +
        ", your heart begins to race, and you feel energy bursting from" +
        " your every pore.\n");
    reset_all_boosts();
    if (IS_PLAYER_OBJECT(wearer))
        IMBUE_LOGGER->log("haste", sprintf("%s  +%d to %d  haste/%s (%d)",
            capitalize(wearer->query_real_name()),
            BOOST_AMOUNT[query_imbuement_power_level()-1],
            wearer->query_prop(LIVE_I_QUICKNESS),
            shadow_who->short(),
            query_id()));
} /* do_wear */


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

    str += "This object has been given a random magic mod that gives "
         + BOOST_AMOUNT[Power_Level-1] + " points of quickness.\n";
    return str;
} /* stat_object */

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
    return CA_POWER_DESC[Power_Level] + " whine is coming from this object.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The whine emanating from the "
      + shadow_who->short() + " abruptly ceases.\n";
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
    return "This object contains a powerful magic enchantment which imbues "
      + "its user with a " +POWER_LEVEL_DESC[Power_Level] + "-level increase "
      + "in speed!";
} /* query_imbue_info */


/*
 * Function name: tell_owner
 * Description  : Give a message to the owner, if still existant
 * Arguments    : object owner - the owner
 *                string msg - the message to show them
 */
static void
tell_owner(object owner, string msg)
{
    if (owner)
    {
        owner->catch_tell(msg);
    }
} /* tell_owner */

/*
 * Function:    calculate_boost
 * Description: Uses the defines at the top of the file to determine
 *              how much this imbue should boost if it were used
 *              alone.
 */
public int
calculate_boost()
{
    int boost = BOOST_AMOUNT[query_imbuement_power_level() - 1];
    return boost;
}

/*
 * Function:    remove_boost
 * Description: Call to actually remove the boost
 */
public void
remove_boost()
{
    if (Boost == 0)
    {
        return;
    }

    object owner = query_owner();
    owner->dec_prop(LIVE_I_QUICKNESS, Boost);
    Boost = 0; // reset boost
}

/*
 * Function:    add_boost
 * Description: Adds the boost to the owner. The argument of
 *              factor applies when there are multiple boosts for
 *              the same imbue. We topologically sort the boosts
 *              and reduce the power for each successive boost.
 */
public void
add_boost(int factor = 0)
{
    object owner = query_owner();
    remove_boost(); // always ensure that we remove any residual boost
    Boost = ftoi(itof(calculate_boost()) * pow(0.62, itof(factor)));
    owner->inc_prop(LIVE_I_QUICKNESS, Boost);
}

/*
 * Function:    reset_all_boosts
 * Description: Called for every wear/wield and unwield/remove to recalculate
 *              the correct amount of boost to have.
 */
public void
reset_all_boosts()
{
    object * all_items = find_all_same_imbuement_items();
    for (int index = 0; index < sizeof(all_items); index++)
    {
        object boost_item = all_items[index];
        if (boost_item == shadow_who)
        {
            add_boost(index);
        }
        else
        {
            boost_item->add_boost(index);
        }
    }
}

