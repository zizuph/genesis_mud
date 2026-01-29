/*
 *  /d/Genesis/imbuement/shadows/effect_light_shadow.c
 *
 *  This shadow makes an item generate light.
 *
 *  2010/09/11 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <macros.h>

inherit SHADOW_DIR + "imbuement_shadow";

/* Definitions */
#define LEVELS           ({ 1, 3, 10 })

/* Global Variables */
public int               Power_Level = 1;
//public string            old_prop;
public int               Active = 0;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
public void              do_unwield(object who);
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear();
public void              do_remove(object who);
public string            query_imbue_info();
public string            stat_object();
public string            dispel_msg_hook();
varargs public mixed     long(string str, object for_obj);
public mixed             query_prop(string prop);


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
                           "aura of light",
                           "dark",
                           "light",
                           "dark aura",
                           "faint aura",
                           "faint aura of light",
                           "pronounced aura",
                           "pronounced aura of light",
                           "intense aura",
                           "intense aura of light",
                           "gleaming aura",
                           "gleaming aura of light" }) );

    set_add_item_desc("A gleaming aura of light fills the air directly"
      + " around the " + shadow_who->short() + ". What strange magic"
      + " is this?\n");

    set_nullstone_type("morning");

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
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    if (res >= 0)
    {
        set_alarm(0.0, 0.0, do_wield);
    }

    set_add_item_desc("A gleaming aura of light fills the air directly"
      + " around the " + shadow_who->short() + ". and has expanded"
      + " to fill the entire area! What strange magic is this?\n");


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
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &do_unwield(shadow_who->query_wielded()));
    }

    set_add_item_desc("A gleaming aura of light fills the air directly"
      + " around the " + shadow_who->short() + ". What strange magic"
      + " is this?\n");

    return res;
} /* unwield */


/*
 * Function name:        do_wield
 * Description  :        The actual message display and light modification.
 */
public void
do_wield()
{
    write("As you wield the " + shadow_who->short() +
        ", a shimmering sheet of light spreads out from it, filling the area" +
         " with illumination.\n");
    //old_prop = shadow_who->query_prop_setting(OBJ_I_LIGHT);
    //shadow_who->inc_prop(OBJ_I_LIGHT, LEVELS[Power_Level-1]);
    Active = 1;
} /* do_wield */


/*
 * Function name:        do_unwield
 * Description  :        The actual message display and light modification.
 */
public void
do_unwield(object who)
{
    who->catch_tell("As you release the " + shadow_who->short() +
            ", the brilliant illumination in the area is drawn back into it" +
            " and absorbed.\n");
    //shadow_who->dec_prop(OBJ_I_LIGHT, old_prop);
    Active = 0;
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
 * Description  :        Show message and remove light when removing
 *                       the armour.
 * Returns      :        int - It could be removed or not
 */
public mixed
remove(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();

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
do_wear()
{
    write("As you wear the " + shadow_who->short() +
        ", a shimmering sheet of light spreads out from it, filling the area" +
         " with illumination.\n");
    //old_prop = shadow_who->query_prop_setting(OBJ_I_LIGHT);
    //shadow_who->add_prop(OBJ_I_LIGHT, LEVELS[Power_Level-1]);
    Active = 1;
} /* do_wear */


/*
 * Function name:        do_remove
 * Description  :        The actual message display and light modification.
 */
public void
do_remove(object who)
{
    who->catch_tell("As you remove the " + shadow_who->short() +
            ", the brilliant illumination in the area is drawn back into it" +
            " and absorbed.\n");
    //shadow_who->add_prop(OBJ_I_LIGHT, old_prop);
    Active = 0;
} /* do_remove */


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
        + POWER_DESC[Power_Level] + " amounts of light to flow into the room"
        + " in which it is put to use!";
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
    return "The aura of light surrounding " + POWER_DESC[Power_Level]
        + " pulses suddenly, and is gone.\n";
} /* dispel_msg_hook */


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
      + CA_POWER_DESC[Power_Level] + " aura of light surrounds this object.\n";
} /* long */


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