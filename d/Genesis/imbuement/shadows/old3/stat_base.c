/*
 *  /d/Genesis/imbuement/shadows/stat_boost_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  stat boosts to a weapon.
 *
 *  2010/08/31 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

//#include <formulas.h>
//#include <macros.h>
//#include <stdproperties.h>
#include <state_desc.h>

/* Definitions */
//#define BOOST_AMOUNT        ({25, 50, 100})
#define BOOST_AMOUNT        ({18.75, 37.5, 75.00})
#define BOOST_MIN           ({12, 25, 50})
#define BOOST_MAX           ({37, 75, 150})

/* Global Variables */
public int               Power_Level = 1;
public int               Stat;
public int               Boost;
public string            Desc, Wieldmsg, Unwieldmsg;

/* Prototypes */
public void              init_statboost(int lvl, int stat, string desc,
                             string wieldmsg, string unwieldmsg);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
//public mixed             wield_me();
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear();
public string            stat_object();
varargs public mixed     long(string str, object for_obj);
public string            query_imbue_info();


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

    Power_Level = lvl;
    Stat = stat;
    Desc = desc;
    Wieldmsg = wieldmsg;
    Unwieldmsg = unwieldmsg;
    shadow_who->set_wf(this_object());
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
 * Description  :        Show message and remove stat boost when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wielder = shadow_who->query_wielded();
    int cur = wielder->query_stat_extra(Stat);

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &wielder->catch_tell("As you release the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n"));
//        wielder->set_stat_extra(Stat, cur - BOOST_AMOUNT[Power_Level-1]);
        wielder->set_stat_extra(Stat, cur - Boost);

    }
    return res;
} /* unwield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and stat modification.
 */
public void
do_wield()
{
    object wielder = shadow_who->query_wielded();
    int cur = wielder->query_stat_extra(Stat);
    Boost = ftoi(itof(wielder->query_stat(Stat)) *
        (BOOST_AMOUNT[Power_Level-1] / 100.0));
    Boost = max(Boost, BOOST_MIN[Power_Level-1]);
    Boost = min(Boost, BOOST_MAX[Power_Level-1]);

    write("As you wield the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
//    wielder->set_stat_extra(Stat, cur + BOOST_AMOUNT[Power_Level-1]);
    wielder->set_stat_extra(Stat, cur + Boost);

} /* do_wield */

/*
 * Function name:        wield_me
 * Description  :        Show message and add stat boost when wielding
 *                       the weapon.
 * Returns      :        mixed - Result from object wield_me
 */
/*public mixed
wield_me(object obj)
{
    int res = shadow_who->wield_me();
    if (res == 1)
    {
        write("As you wield the " + shadow_who->short() +
            ", " + Wieldmsg + "\n");
    }
    return res;
} /* unwield */


/*
 * Function name:        wear
 * Description  :        Show message and add stat boost when wearing
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
 * Description  :        Show message and remove stat boost when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wearer = shadow_who->query_worn();
    int cur = wearer->query_stat_extra(Stat);

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &wearer->catch_tell("As you remove the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n"));
//        wearer->set_stat_extra(Stat, cur - BOOST_AMOUNT[Power_Level-1]);
        wearer->set_stat_extra(Stat, cur - Boost);

    }
    return res;
} /* remove */

/*
 * Function name:        do_wear
 * Description  :        The actual message display and stat modification.
 */
public void
do_wear()
{
    object wearer = shadow_who->query_worn();
    int cur = wearer->query_stat_extra(Stat);
    Boost = ftoi(itof(wearer->query_stat(Stat)) *
        (BOOST_AMOUNT[Power_Level-1] / 100.0));
    Boost = max(Boost, BOOST_MIN[Power_Level-1]);
    Boost = min(Boost, BOOST_MAX[Power_Level-1]);

    write("As you wear the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
//    wearer->set_stat_extra(Stat, cur + BOOST_AMOUNT[Power_Level-1]);
    wearer->set_stat_extra(Stat, cur + Boost);

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

    str += "This weapon has been given a random magic mod that gives a " +
        BOOST_MIN[Power_Level-1] + " to " + BOOST_MAX[Power_Level-1] +
        " point boost to " + SD_LONG_STAT_DESC[Stat] + ".\n";

    //         + " a " + BOOST_AMOUNT[Power_Level-1] + " point boost to "
    //         + SD_LONG_STAT_DESC[Stat] + ".\n";
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
      + CA_POWER_DESC[Power_Level] + " smell of " + Desc + " emanates from"
      + " its surface.\n";
} /* long */


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
      + POWER_LEVEL_DESC[Power_Level] + " boost to your "
      + SD_LONG_STAT_DESC[Stat] + " whilst wielded!";
} /* query_imbue_info */