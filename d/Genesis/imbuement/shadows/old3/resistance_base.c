/*
 *  /d/Genesis/imbuement/shadows/resistance_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  resistances to an item.
 *
 *  2010/09/09 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

//#include <formulas.h>
//#include <macros.h>
//#include <stdproperties.h>
#include <state_desc.h>

/* Definitions */
#define BOOST_AMOUNT        ({10, 20, 30})

/* Global Variables */
public int               Power_Level = 1;
public string            Res;
public string            Desc, Restext, Resdesc;

/* Prototypes */
public void              init_resistance(int lvl, string res, string restext,
                            string resdesc, string desc);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear();
public string            stat_object();
varargs public mixed     long(string str, object for_obj);
public string            query_imbue_info();


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

    Power_Level = lvl;
    Res = res;
    Desc = desc;
    Restext = restext;
    Resdesc = resdesc;
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
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
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
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wearer = shadow_who->query_worn();

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &wearer->catch_tell("Removing the " +
            shadow_who->short() + ", you feel a strange sense of" +
            " protection life from you.\n"));
        wearer->remove_magic_effect(this_object());

    }
    return res;
} /* remove */


/*
 * Function name:        do_wear
 * Description  :        The actual message display and resistance modification.
 */
public void
do_wear()
{
    object wearer = shadow_who->query_worn();

    wearer->catch_tell("As you wear the " + shadow_who->short() +
        ", an uncanny feeling of additional protection pulses" +
        " through you.\n");
    wearer->add_magic_effect(this_object());

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

    str += "This item has been given a random magic mod that gives a "
         + BOOST_AMOUNT[Power_Level-1] + " point " 
         + Restext + " resistance.\n";
    return str;
} /* stat_object */


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
      + Desc + "\n";
} /* long */


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
      + " a " + POWER_LEVEL_DESC[Power_Level] + "-level resistance to "
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
    int *res_arr;
    if ((type == Res) && ((protectee == shadow_who->query_wielded()) || 
        (protectee == shadow_who->query_worn())))
    {
        res_arr = shadow_who->query_magic_protection(type, protectee);
        if (!res_arr)
            return ({ BOOST_AMOUNT[Power_Level-1], 1 });
        else
        {
            res_arr[0] += BOOST_AMOUNT[Power_Level-1];
            return res_arr;
        }
    }
    else
        return shadow_who->query_magic_protection(type, protectee);
} /* query_magic_protection */