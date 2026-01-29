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

inherit SHADOW_DIR + "imbuement_shadow";

#include <ss_types.h>

/* Definitions */
#define BOOST_AMOUNT        ({12, 25, 50})
#define BOOST_THRESH        ({ ({3,6,9,11}), ({6,13,19,24}), ({13,25,38,49}) })

/* Global Variables */
public int               Skill;
public string            Desc, Skilltext, Wieldmsg, Unwieldmsg;
public object            oldwf;
public int               Active, Boost;

/* Prototypes */
public void              init_skillboost(int lvl, int skill, string skilltext, 
                             string desc, string wieldmsg, string unwieldmsg);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield(int num);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear(int num);
static void              add_effect(object owner);
static void              remove_effect(object owner);
public string            stat_object();
public string            query_imbue_info();
static void              tell_owner(object owner, string msg);
public int               calculate_boost();
public void              remove_boost();
public void              add_boost(int factor = 0);
public void              reset_all_boosts();

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

    Skill = skill;
    Desc = desc;
    Skilltext = skilltext;
    Wieldmsg = "a strange tingle goes through your body.";
    Unwieldmsg = "you suffer an involuntary shudder.";
    oldwf = shadow_who->query_wf();
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
 * Description  :        Show message and remove skill boost when unwielding
 *                       the weapon.
 * Returns      :        int - It could be wielded or not
 */
public mixed
unwield(object obj)
{
    mixed res = oldwf->unwield(obj);
    object wielder = shadow_who->query_wielded();

    if (stringp(res))
    {
        // res contains a failure message. don't unwield weapon.
        return res;
    }

    if (res >= 0)
    {
        tell_owner(wielder, "As you release the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n");
        remove_effect(wielder);
    }

    return res;
} /* unwield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and skill modification.
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

    wielder->catch_tell("As you wield the " + shadow_who->short() +
        ", " + Wieldmsg + "\n");

    add_effect(wielder);
} /* do_wield */

/*
 * Function name:        wear
 * Description  :        Show message and add skill boost when wearing
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
 * Description  :        Show message and remove skill boost when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    mixed res = oldwf->remove(obj);
    object wearer = shadow_who->query_worn();

    if (stringp(res))
    {
        // Failure stored in "res". Don't remove.
        return res;
    }

    if (res >= 0)
    {
        tell_owner(wearer, "As you remove the " +
            shadow_who->short() + ", " + Unwieldmsg + "\n");
        remove_effect(wearer);
    }
    return res;
} /* remove */

/*
 * Function name:        do_wear
 * Description  :        The actual message display and skill modification.
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
        ", " + Wieldmsg + "\n");

    add_effect(wearer);
} /* do_wear */

/*
 * Function name:        add_effect
 * Description  :        Add the skill boost
 * Arguments    :        object - living to add effects to
 */
static void
add_effect(object owner)
{
    int extra = owner->query_skill_extra(Skill);
    int total = owner->query_skill(Skill);
    int *thresh = BOOST_THRESH[query_imbuement_power_level()-1];

    reset_all_boosts();

    if (Boost <= 0)
        owner->catch_tell("The feeling seems to have just been an illusion, " +
            "however.\n");
    else if (Boost <= thresh[0])
        owner->catch_tell("The feeling seems to dull almost entirely for " +
            "you, however.\n");
    else if (Boost <= thresh[1])
        owner->catch_tell("The feeling seems to dull quite a bit for you, " +
            "however.\n");
    else if (Boost <= thresh[2])
        owner->catch_tell("The feeling seems to dull somewhat for you, " +
            "however.\n");
    else if (Boost <= thresh[3])
        owner->catch_tell("The feeling seems to dull slightly for you, " +
            "however.\n");            
} /* add_effect */


/*
 * Function name:        remove_effect
 * Description  :        Remove the skill boost
 * Arguments    :        object - living to remove effects from
 */
static void
remove_effect(object owner)
{
    remove_boost();
    set_alarm(0.0, 0.0, &reset_all_boosts());
} /* remove_effect */


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

    str += "This item has been given a random magic mod that gives"
         + " a " + BOOST_AMOUNT[query_imbuement_power_level()-1] + " point boost to "
         + Skilltext + ".\n";
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
    return "This item has been imbued with a strange magic which gives the"
      + " user a " + POWER_LEVEL_DESC[query_imbuement_power_level()] + "-grade boost in "
      + Skilltext + " skill.";
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
 *              how much this skill should be boosted if it were used
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
    int current_extra = owner->query_skill_extra(Skill);
    owner->set_skill_extra(Skill, current_extra - Boost);
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
//    remove_boost(); // always ensure that we remove any residual boost
    Boost = ftoi(itof(calculate_boost()) * pow(0.62, itof(factor)));
    int current_extra = owner->query_skill_extra(Skill);
    int total = owner->query_base_skill(Skill) + current_extra;
    // We need to adjust boost if it causes the skill to exceed 100
    Boost = max(0, min(100, total + Boost) - total);
    // There is a flaw in /std/living for skills that haven't been instantiated
    // We instantiate it so that it will display properly in the player
    if (!total && !owner->query_base_skill(Skill))
    {
        owner->set_skill(Skill, 0);
    }
    owner->set_skill_extra(Skill, current_extra + Boost);
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
    // First remove all boost items. Need to do this in order to have
    // a clean slate during calculating higher level boosts that may
    // go over sup guru
    foreach (object boost_item : all_items)
    {
        if (boost_item == shadow_who)
        {
            remove_boost();
        }
        else
        {
            boost_item->remove_boost();
        }
    }
    // Now add the boosts one by one
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

