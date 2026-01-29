/*
 *  /d/Genesis/imbuement/shadows/resistance_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  resistances to an item.
 *
 *  2010/09/09 Lavellan
 *
 *  The 'quietstone' imbuement that provided flat magic resistance
 *  for all magic types has been reduced, so that we now have imbues
 *  that provide specific and high resistance values, and one that
 *  provides broad but lower value resistance.
 *  2019/07/19 Arman
 *
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

//#include <formulas.h>
//#include <macros.h>
#include <stdproperties.h>
#include <state_desc.h>

/* Definitions */
#define BOOST_AMOUNT            ({10, 20, 40})
#define BOOST_AMOUNT_GENERAL    ({4, 8, 16})

/* Global Variables */
public int               Boost = 0;
public string            Res;
public string            Desc, Restext, Resdesc;
public object            oldwf;

/* Prototypes */
public void              init_resistance(int lvl, string res, string restext,
                            string resdesc, string desc);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear(int num);
public string            stat_object();
public string            query_imbue_info();
static void              tell_owner(object owner, string msg);
public int               calculate_boost();
public void              remove_boost();
public void              add_boost(int factor = 0);
public void              reset_all_boosts();


/*
 * Function name:        init_resistance
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 *                       string res - resistance property to modify
 *                       string restext - name of the resistance
 *                       string resdesc - description of the resistance
 *                       string desc - Line to add to weapon long
 */
public void
init_resistance(int lvl, string res, string restext, string resdesc,
    string desc)
{   
    ::init_imbue_shadow(lvl);

    Res = res;
    Desc = desc;
    Restext = restext;
    Resdesc = resdesc;
    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());
} /* init_resistance */


/*
 * Function name:        wear
 * Description  :        Show message and add resistance when wearing
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
 * Description  :        Show message and remove resistance when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    mixed res = oldwf->remove(obj);
    object wearer = shadow_who->query_worn();

    if (stringp(res)) return res;
    if ((res >= 0) && (calling_function(-5) != "recursive_rm"))
    {
        set_alarm(0.0, 0.0, &tell_owner(wearer, "Removing the " +
            shadow_who->short() + ", you feel a strange sense of" +
            " protection lift from you.\n"));
        wearer->remove_magic_effect(this_object());
        remove_boost();
        set_alarm(0.0, 0.0, &reset_all_boosts());
    }
    return res;
} /* remove */


/*
 * Function name:        do_wear
 * Description  :        The actual message display and resistance modification.
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

    wearer->catch_tell("As you wear the " + shadow_who->short() +
        ", an uncanny feeling of additional protection pulses" +
        " through you.\n");
    wearer->add_magic_effect(this_object());
    reset_all_boosts();
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

    if(Res == MAGIC_I_RES_MAGIC)
        str += "This item has been given a random magic mod that gives a "
             + BOOST_AMOUNT_GENERAL[query_imbuement_power_level()-1] + " point " 
             + Restext + " resistance.\n";
    else
        str += "This item has been given a random magic mod that gives a "
             + BOOST_AMOUNT[query_imbuement_power_level()-1] + " point " 
             + Restext + " resistance.\n";
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
    return Desc;
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
    return "This item has been imbued with powerful magic which gives the user"
      + " a " + POWER_LEVEL_DESC[query_imbuement_power_level()] + "-level resistance to "
      + Resdesc + "!";
} /* query_imbue_info */

/*
 * Function name: query_magic_protection
 * Description  : Add our protection value
 * Arguments    : string type - type of magic protection asked about
 *                object protectee - object asked about
 * Returns      : int * - array of ({ strength, cumulative }) including boost
 */
varargs public mixed
query_magic_protection(string type, object protectee = previous_object())
{
    int * res_arr = shadow_who->query_magic_protection(type, protectee);
    if ((type == Res) && ((protectee == shadow_who->query_wielded()) || 
        (protectee == shadow_who->query_worn())))
    {
        if (!pointerp(res_arr))
        {
            return ({ Boost, 1 });
        }
        else
        {
            return ({ res_arr[0] + Boost, res_arr[1] });
        }
    }
    
    return res_arr;
} /* query_magic_protection */


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
    int boost;

    // Boost is reduced for broad magic resistance coverage
    if(Res == MAGIC_I_RES_MAGIC)
        boost = BOOST_AMOUNT_GENERAL[query_imbuement_power_level() - 1];
    else
        boost = BOOST_AMOUNT[query_imbuement_power_level() - 1];
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

