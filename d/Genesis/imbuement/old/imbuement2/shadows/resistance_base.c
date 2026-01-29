/*
 *  /d/Genesis/imbuement/shadows/resistance_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  resistances to a weapon.
 *
 *  2010/09/09 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_BASE;

//#include <formulas.h>
//#include <macros.h>
//#include <stdproperties.h>
#include <state_desc.h>

/* Definitions */
#define BOOST_AMOUNT        ({10, 20, 30})

/* Global Variables */
public int               Power_Level = 1;
public string            Res;
public string            Desc, Restext, Wieldmsg, Unwieldmsg;

/* Prototypes */
public void              init_resistance(int lvl, string res, string restext,
                             string desc, string wieldmsg, string unwieldmsg);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
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
 *                       string desc - Line to add to weapon long
 *                       string wieldmsg, unwieldmsg - message to show when
 *                          (un)wielding
 */
public void
init_resistance(int lvl, string res, string restext, string desc, 
    string wieldmsg, string unwieldmsg)
{   
    ::init_imbue_shadow(lvl);

    Power_Level = lvl;
    Res = res;
    Desc = desc;
    Restext = restext;
    Wieldmsg = wieldmsg;
    Unwieldmsg = unwieldmsg;
    shadow_who->set_wf(this_object());
} /* init_resistance */


/*
 * Function name:        wield
 * Description  :        Show message and add resistance when wielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
wield(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, do_wield);
    }
    return res;
} /* wield */


/*
 * Function name:        unwield
 * Description  :        Show message and remove resistance when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wielder = shadow_who->query_wielded();

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &write("As you release the " + shadow_who->short() +
            ", " + Unwieldmsg + "\n"));
        wielder->remove_magic_effect(this_object());

    }
    return res;
} /* wield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and resistance modification.
 */
public void
do_wield()
{
    object wielder = shadow_who->query_wielded();

    write("As you wield the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
    wielder->add_magic_effect(this_object());

} /* do_wield */


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
    return "This item has been imbued with magic that gives a "
      + POWER_LEVEL_DESC[Power_Level] + " boost to your "
      + Restext + " resistance whilst wielded!";
} /* query_imbue_info */


varargs public mixed
query_magic_protection(string type, object protectee = previous_object())
{
    if ((type = Res) && (protectee = shadow_who->query_wielded()))
        return shadow_who->query_magic_protection(type, protectee) +
            BOOST_AMOUNT[Power_Level-1];

    return shadow_who->query_magic_protection(type, protectee);
}