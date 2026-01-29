/*
 *  /d/Genesis/imbuement/shadows/effect_darkness_shadow.c
 *
 *  This shadow makes an item generate darkness.
 *
 *  2010/09/11 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <macros.h>

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define LEVELS           ({ -1, -3, -10 })

/* Global Variables */
//public string            old_prop;
public int               Active = 0;
public object            oldwf;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield(int num);
public void              do_unwield(object who);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear(int num);
public void              do_remove(object who);
public string            query_imbue_info();
public string            stat_object();
public string            dispel_msg_hook();
public mixed             query_prop(string prop);
public void              active(int active);


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
                           "aura of darkness",
                           "dark",
                           "darkness",
                           "dark aura",
                           "faint aura",
                           "faint aura of darkness",
                           "pronounced aura",
                           "pronounced aura of darkness",
                           "intense aura",
                           "intense aura of darkness",
                           "dense aura",
                           "dense aura of darkness" }) );

    set_add_item_desc("A dense aura of darkness clings to the air"
      + " directly surrounding the " + shadow_who->short() + ". Some"
      + " powerful magic must be at work here!\n");

    set_nullstone_type("night");

    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());
} /* init_imbue_shadow */


/*
 * Function name:        wield
 * Description  :        Show message and add light when wielding
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
 * Description  :        Show message and remove light when unwielding
 *                       the weapon.
 * Returns      :        int - It could be unwielded or not
 */
public mixed
unwield(object obj)
{
    mixed res = oldwf->unwield(obj);

    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &do_unwield(shadow_who->query_wielded()));
    }

    return res;
} /* unwield */


/*
 * Function name:        do_wield
 * Description  :        The actual message display and light modification.
 */
public void
do_wield(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wield(num);
        return;
    }
    write("As you wield the " + shadow_who->short() + ", a murky blanket of" +
        " darkness washes out from it, filling the area with its gloom.\n");
    active(1);
} /* do_wield */


/*
 * Function name:        do_unwield
 * Description  :        The actual message display and light modification.
 */
public void
do_unwield(object who)
{
    who->catch_tell("As you release the " + shadow_who->short() +
        ", the darkness in the area rushes suddenly back into it and is" +
        " swallowed from view.\n");
    active(0);
} /* do_unwield */


/*
 * Function name:        wear
 * Description  :        Show message and add light when wearing
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
 * Description  :        Show message and remove light when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    mixed res = oldwf->remove(obj);

    if (stringp(res)) return res;
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &do_remove(shadow_who->query_worn()));
    }
    return res;
} /* remove */


/*
 * Function name:        do_wear
 * Description  :        The actual message display and light modification.
 */
public void
do_wear(int num = 0)
{
    if (num && (num != Shadow_Num))
    {
        shadow_who->do_wear(num);
        return;
    }
    write("As you wear the " + shadow_who->short() + ", a murky blanket of" +
        " darkness washes out from it, filling the area with its gloom.\n");
    active(1);
} /* do_wear */


/*
 * Function name:        do_remove
 * Description  :        The actual message display and light modification.
 */
public void
do_remove(object who)
{
    who->catch_tell("As you remove the " + shadow_who->short() +
        ", the darkness in the area rushes suddenly back into it and is" +
        " swallowed from view.\n");
    active(0);
} /* do_remove */


/*
 * Function name: active
 * Description  : Change the light levels
 * Arguments    : int active - light is on or not
 */
public void
active(int active)
{
    if (active)
    {
        Active = 1;
        environment(shadow_who)->notify_change_prop(OBJ_I_LIGHT, 
            shadow_who->query_prop(OBJ_I_LIGHT) + LEVELS[Power_Level-1],
            shadow_who->query_prop(OBJ_I_LIGHT));
        set_add_item_desc("A dense aura of darkness clings to the air"
          + " directly surrounding the " + shadow_who->short() + ", and"
          + " has in fact expanded to fill the entire area. Some"
          + " powerful magic must be at work here!\n");
    }
    else
    {
        Active = 0;
        environment(shadow_who)->notify_change_prop(OBJ_I_LIGHT, 
            shadow_who->query_prop(OBJ_I_LIGHT),
            shadow_who->query_prop(OBJ_I_LIGHT) + LEVELS[Power_Level-1]);
        set_add_item_desc("A dense aura of darkness clings to the air"
          + " directly surrounding the " + shadow_who->short() + ". Some"
          + " powerful magic must be at work here!\n");
    }
} /* active */

/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "This item has been imbued with magic that causes "
        + POWER_DESC[Power_Level] + " amounts of darkness.";
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

    str += "This item has been given an imbuement that generates power "
            + LEVELS[Power_Level-1] + " light whilst in use.\n";
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
    return "The aura of darkness surrounding the " + shadow_who->short()
        + " pulses suddenly, and is gone.\n";
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
    return CA_POWER_DESC[Power_Level] + " aura of darkness surrounds this "
        + "object.";
}

/*
 * Function name: query_prop
 * Description  : Return our altered property
 * Arguments    : mixed prop - the name of the property
 * Returns      : mixed - the value of the property, possibly modified
 */
public mixed
query_prop(string prop)
{
    if ((prop == OBJ_I_LIGHT) && (Active))
        return shadow_who->query_prop(prop) + LEVELS[Power_Level-1];
    else
        return shadow_who->query_prop(prop);
} /* query_prop */
