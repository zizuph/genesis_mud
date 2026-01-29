/*
 *  /d/Genesis/imbuement/shadows/effect_darkvision_shadow.c
 *
 *  This shadow gives darkvision to the user.
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
public string            old_prop;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
public mixed             wear(object obj);
public mixed             remove(object obj);
public void              do_wear();
public string            query_imbue_info();
public string            stat_object();
public string            dispel_msg_hook();
varargs public mixed     long(string str, object for_obj);

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
    
    set_add_item_array( ({ "sparkle",
                           "faint sparkle",
                           "pronounced sparkle",
                           "intense sparkle", }) );

    set_add_item_desc("The sparkle that meets your eyes as you peer at"
      + " the " + shadow_who->short() + " is neither light nor darkness,"
      + " but something entirely other. The effect is most beguiling!\n");

    set_nullstone_type("torch");

    shadow_who->set_wf(this_object());
} /* init_imbue_shadow */


/*
 * Function name:        wield
 * Description  :        Show message and add darkvision when wielding
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
 * Description  :        Show message and remove darkvision when unwielding
 *                       the weapon.
 * Returns      :        int - It could be unwielded or not
 */
public mixed
unwield(object obj)
{
    function wf = shadow_who->query_wf;
    int res = shadow_who->wf();
    object wielder = shadow_who->query_wielded();

    if (res >= 0)
    {
        set_alarm(0.0, 0.0, &wielder->catch_tell("As you release the "
            + shadow_who->short() + ", your vision blurs momentarily."
            + " Upon clearing, your eyes feel somehow less apt.\n"));
        wielder->add_prop(LIVE_I_SEE_DARK, old_prop);
    }
    return res;
} /* unwield */


/*
 * Function name:        do_wield
 * Description  :        The actual message display and skill modification.
 */
public void
do_wield()
{
    object wielder = shadow_who->query_wielded();
    int old_see_dark;
    
    wielder->catch_tell("As you wield the " + shadow_who->short() + ", your"
        + " eyes blur momentarily, and then come into even greater focus than"
        + " before.\n");
    old_prop = wielder->query_prop_setting(LIVE_I_SEE_DARK);
    old_see_dark = wielder->query_prop(LIVE_I_SEE_DARK);
    wielder->add_prop(LIVE_I_SEE_DARK, old_see_dark + LEVELS[Power_Level-1]);
} /* do_wield */


/*
 * Function name:        wear
 * Description  :        Show message and add darkvision when wearing
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
 * Description  :        Show message and remove darkvision when removing
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
        set_alarm(0.0, 0.0, &wearer->catch_tell("As you remove the "
            + shadow_who->short() + ", your vision blurs momentarily."
            + " Upon clearing, your eyes feel somehow less apt.\n"));
        wearer->add_prop(LIVE_I_SEE_DARK, old_prop);
    }
    return res;
} /* remove */


/*
 * Function name:        do_wear
 * Description  :        The actual message display and property modification.
 */
public void
do_wear()
{
    object wearer = shadow_who->query_worn();
    int old_see_dark;
    
    wearer->catch_tell("As you wield the " + shadow_who->short() + ", your"
        + " eyes blur momentarily, and then come into even greater focus than"
        + " before.\n");
    old_prop = wearer->query_prop_setting(LIVE_I_SEE_DARK);
    old_see_dark = wearer->query_prop(LIVE_I_SEE_DARK);
    wearer->add_prop(LIVE_I_SEE_DARK, old_see_dark + LEVELS[Power_Level-1]);
} /* do_wield */


/*
 * Function name:        query_imbue_info
 * Description  :        Provide info on the effect of this imbuement
 *                       to be used by a successful identify spell attempt
 * Returns      :        string - the info
 */
public string
query_imbue_info()
{
    return "This item grants the user the ability to see through "
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

    str += "This weapon has been given an imbuement that gives the wielder "
            + "power " + LEVELS[Power_Level-1] + " darkvision.\n";
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
    return "The sparkle coming from the " + shadow_who->short()
        + " winks out of existance.\n";
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
      + CA_POWER_DESC[Power_Level] + " sparkle bewitches your senses as"
      + " you peer at it.\n";
} /* long */