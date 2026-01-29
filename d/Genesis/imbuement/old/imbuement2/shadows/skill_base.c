/*
 *  /d/Genesis/imbuement/shadows/skill_boost_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  skill boosts to an item.
 *
 *  2010/09/09 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_BASE;

//#include <formulas.h>
//#include <macros.h>
//#include <stdproperties.h>
#include <ss_types.h>

/* Definitions */
#define BOOST_AMOUNT        ({1, 3, 5})

/* Global Variables */
public int               Power_Level = 1;
public int               Skill;
public string            Desc, Skilltext, Wieldmsg, Unwieldmsg;

/* Prototypes */
public void              init_skillboost(int lvl, int skill, string skilltext, 
                             string desc, string wieldmsg, string unwieldmsg);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
//public mixed             wield_me();
public string            stat_object();
varargs public mixed     long(string str, object for_obj);
public string            query_imbue_info();


/*
 * Function name:        init_skillboost
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 *                       int skill - the skill to boost
 *                       string skilltext - name of the skill 
 *                       string desc - Line to add to weapon long
 *                       string wieldmsg, unwieldmsg - message to show when
 *                          (un)wielding
 */
public void
init_skillboost(int lvl, int skill, string skilltext, string desc, 
    string wieldmsg = 0, string unwieldmsg = 0)
{   
    ::init_imbue_shadow(lvl);

    Power_Level = lvl;
    Skill = skill;
    Desc = desc;
    Skilltext = skilltext;
//    Wieldmsg = wieldmsg;
//    Unwieldmsg = unwieldmsg;
    Wieldmsg = "a strange tingle goes through your body.";
    Unwieldmsg = "you suffer an involuntary shudder.";
    shadow_who->set_wf(this_object());
} /* init_skillboost */


/*
 * Function name:        wield
 * Description  :        Show message and add skill boost when wielding
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
 * Description  :        Show message and remove skill boost when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wielder = shadow_who->query_wielded();
    int cur = wielder->query_skill_extra(Skill);

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &write("As you release the " + shadow_who->short() +
            ", " + Unwieldmsg + "\n"));
        wielder->set_skill_extra(Skill, cur - BOOST_AMOUNT[Power_Level-1]);
        //  Special handling for sneak, give hide skill too
        if (Skill == SS_SNEAK)
        {
            cur = wielder->query_skill_extra(SS_HIDE);
            wielder->set_skill_extra(SS_HIDE, cur - 
                BOOST_AMOUNT[Power_Level-1]);
        }
    }
    return res;
} /* wield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and skill modification.
 */
public void
do_wield()
{
    object wielder = shadow_who->query_wielded();
    int cur = wielder->query_skill_extra(Skill);

    write("As you wield the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");
    wielder->set_skill_extra(Skill, cur + BOOST_AMOUNT[Power_Level-1]);
    //  Special handling for sneak, give hide skill too
    if (Skill == SS_SNEAK)
    {
        cur = wielder->query_skill_extra(SS_HIDE);
        wielder->set_skill_extra(SS_HIDE, cur + BOOST_AMOUNT[Power_Level-1]);
    }

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
} /* wield */

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

    str += "This weapon has been given a random magic mod that gives"
         + " a " + BOOST_AMOUNT[Power_Level-1] + " point boost to "
         + Skilltext + ".\n";
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
    return "This item has been imbued with a strange magic which gives the"
      + " user a " + POWER_LEVEL_DESC[Power_Level] + "-grade boost in "
      + Skilltext + " skill.";
} /* query_imbue_info */