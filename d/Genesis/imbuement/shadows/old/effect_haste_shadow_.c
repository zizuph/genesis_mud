/*
 *  /d/Genesis/imbuement/shadows/haste_shadow.c
 *
 *  Gives haste to wielder
 *
 *  2010/09/09 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

#include <macros.h>

/* Definitions */
#define BOOST_AMOUNT        ({15, 30, 45})

/* Global Variables */
public int               Power_Level = 1;

/* Prototypes */
public void              init_imbue_shadow(int lvl);
public mixed             wield(object obj);
public mixed             unwield(object obj);
public void              do_wield();
public string            stat_object();
varargs public mixed     long(string str, object for_obj);
public string            query_imbue_info();


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
    
    set_add_item_array( ({"blah"}) );
    set_add_item_desc("It's a blah.\n");
    
    shadow_who->set_wf(this_object());
} /* init_imbue_shadow */


/*
 * Function name:        wield
 * Description  :        Show message and add quickness when wielding
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
 * Description  :        Show message and remove quickness when unwielding
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
            ", you feel slower.\n"));
        wielder->remove_prop(LIVE_I_QUICKNESS);
    }
    return res;
} /* wield */

/*
 * Function name:        do_wield
 * Description  :        The actual message display and quickness modification.
 */
public void
do_wield()
{
    object wielder = shadow_who->query_wielded();

    write("As you wield the " + shadow_who->short() +
        ", you feel quicker!\n");
    wielder->add_prop(LIVE_I_QUICKNESS, BOOST_AMOUNT[Power_Level-1]);
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

    str += "This weapon has been given a random magic mod that gives"
         + BOOST_AMOUNT[Power_Level-1] + " points of quickness.\n";
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
      + "It looks strange.\n";
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
      + "combat speed whilst wielded!";
} /* query_imbue_info */