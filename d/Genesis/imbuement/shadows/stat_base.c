/*
 *  /d/Genesis/imbuement/shadows/stat_boost_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  stat boosts to a item.
 *
 *  2010/08/31 Lavellan
 *  2013/09/05 Petros - Changed stacking behavior for stat boosts
 */
#pragma strict_types
#include <macros.h>
#include <files.h>
#include <state_desc.h>
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define BOOST_AMOUNT        ({18.75, 37.5, 75.00})
#define BOOST_MIN           ({12, 25, 50})
#define BOOST_MAX           ({20, 40, 80})

/* Global Variables */
public int               Stat;
public int               Boost;
public string            Desc, Wieldmsg, Unwieldmsg;
public object            oldwf;

/* Prototypes */
public void              init_statboost(int lvl, int stat, string desc,
                             string wieldmsg, string unwieldmsg);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield(int num);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear(int num);
public string            stat_object();
public string            query_imbue_info();
static void              tell_owner(object owner, string msg);

/*
 * Function:    calculate_stat_boost
 * Description: Uses the defines at the top of the file to determine
 *              how much this stat should be boosted if it were used
 *              alone.
 */
public int
calculate_stat_boost()
{
    int boost = ftoi(itof(query_owner()->query_base_stat(Stat)) *
                     (BOOST_AMOUNT[query_imbuement_power_level()-1] / 100.0));
    boost = max(boost, BOOST_MIN[query_imbuement_power_level()-1]);
    boost = min(boost, BOOST_MAX[query_imbuement_power_level()-1]);
    return boost;
}

/*
 * Function:    remove_stat_boost
 * Description: Call to actually remove the boost from the stat_extra
 */
public void
remove_stat_boost()
{
    if (Boost == 0)
    {
        return;
    }

    int current_stat_extra = query_owner()->query_stat_extra(Stat);
    query_owner()->set_stat_extra(Stat, current_stat_extra - Boost);
    Boost = 0; // reset boost
}

/*
 * Function:    add_stat_boost
 * Description: Adds the stat boost to the owner. The argument of
 *              factor applies when there are multiple boosts for
 *              the same stat. We topologically sort the boosts
 *              and halve the power for each successive boost.
 */
public void
add_stat_boost(int factor = 0)
{
    remove_stat_boost(); // always ensure that we remove any residual boost
    Boost = ftoi(itof(calculate_stat_boost()) * pow(0.62, itof(factor)));
    int current_stat_extra = query_owner()->query_stat_extra(Stat);
    query_owner()->set_stat_extra(Stat, current_stat_extra + Boost);
}

/*
 * Function:    reset_all_stat_boost_imbue_items
 * Description: Called for every wear/wield and unwield/remove to recalculate
 *              the correct amount of boost to have.
 */
public void
reset_all_stat_boost_imbue_items()
{
    object * all_stat_items = find_all_same_imbuement_items();
    for (int index = 0; index < sizeof(all_stat_items); index++)
    {
        object stat_item = all_stat_items[index];
        if (stat_item == shadow_who)
        {
            add_stat_boost(index);
        }
        else
        {
            stat_item->add_stat_boost(index);
        }
    }
}

/*
 * Function name:        init_statboost
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 *                       int stat - the stat to boost
 *                       string desc - Line to add to weapon long
 *                       string wieldmsg, unwieldmsg - message to show when
 *                          (un)wielding
 */
public void
init_statboost(int lvl, int stat, string desc,
    string wieldmsg, string unwieldmsg)
{   
    ::init_imbue_shadow(lvl);

    Stat = stat;
    Desc = desc;
    Wieldmsg = wieldmsg;
    Unwieldmsg = unwieldmsg;
    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());
    Boost = 0;
} /* init_statboost */


/*
 * Function name:        wield
 * Description  :        Show message and add stat boost when wielding
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
 * Description  :        Show message and remove stat boost when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    mixed res = oldwf->unwield(obj);

    if (stringp(res)) return res;
    if ((res >= 0) && (calling_function(-3) != "recursive_rm"))
    {
        set_alarm(0.0, 0.0, &tell_owner(query_owner(), "As you release the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n"));
        remove_stat_boost();
        set_alarm(0.0, 0.0, &reset_all_stat_boost_imbue_items());
    }
    return res;
} /* unwield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and stat modification.
 */
public void
do_wield(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wield(num);
        return;
    }
    write("As you wield the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
    reset_all_stat_boost_imbue_items();
} /* do_wield */

/*
 * Function name:        wear
 * Description  :        Show message and add stat boost when wearing
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
 * Description  :        Show message and remove stat boost when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    mixed res = oldwf->remove(obj);

    if (stringp(res)) return res;
    if ((res >= 0) && (calling_function(-5) != "recursive_rm"))
    {
        set_alarm(0.0, 0.0, &tell_owner(query_owner(), "As you remove the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n"));
        remove_stat_boost();
        set_alarm(0.0, 0.0, &reset_all_stat_boost_imbue_items());
    }
    return res;
} /* remove */

/*
 * Function name:        do_wear
 * Description  :        The actual message display and stat modification.
 */
public void
do_wear(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wear(num);
        return;
    }
    write("As you wear the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
    reset_all_stat_boost_imbue_items();
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

    str += "This item has been given a random magic mod that gives a " +
        BOOST_MIN[query_imbuement_power_level()-1] + " to " + BOOST_MAX[query_imbuement_power_level()-1] +
        " point boost to " + SD_LONG_STAT_DESC[Stat] + ".\n";

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
    return CA_POWER_DESC[query_imbuement_power_level()] + " smell of " + Desc + " emanates from"
      + " its surface.";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The smell of " + Desc + " coming from the "
      + shadow_who->short() + " is no longer noticable.\n";
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
    return "This item has been imbued with magic that gives a "
      + POWER_LEVEL_DESC[query_imbuement_power_level()] + " boost to your "
      + SD_LONG_STAT_DESC[Stat] + " whilst equipped!";
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
