/*
 *  /d/Genesis/imbuement/shadows/healing_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect heals the wielder every so often
 *
 *  2010/09/13 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

#include <macros.h>

/* Global Variables */
public int               Power_Level = 1;
public int               Heal_Alarm;

/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
public void              heal();
varargs public mixed     long(string str, object for_obj);
public string            dispel_msg_hook();
public string            query_imbue_info();


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

    str += "This weapon has been given a random magic mod that heals the"
         + " wielder every so often.\n";
    return str;
} /* stat_object */


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

    set_add_item_array(   ({ "feeling", "security",
                             "feeling of security", }) );
    set_add_item_desc(
        "It's a feeling of security. You can't see it.\n");

    setuid();
    seteuid(getuid());
    Heal_Alarm = set_alarm(60.0, 60.0, heal);
} /* init_imbue_shadow */


/*
 * Function name: heal
 * Description:   heal the wielder (perhaps)
 */
public void
heal()
{
    object liv = shadow_who->query_wielded();
    string t;
    
    if (liv)
    {
        if (liv->query_hp() < liv->query_max_hp())
        {
            if (sizeof(shadow_who->query_slots()) > 1)
                t = "hands tingle";
            else if (shadow_who->query_slots()[0] == 1024)
                t = "left hand tingles";
            else
                t = "right hand tingles";
            liv->catch_tell("Your " + t + ", and then your wounds"
                + " tingle too.\n");
            liv->heal_hp(Power_Level * 10);
        }
    }
} /* heal */


/*
 * Function name: long
 */
varargs public mixed
long(string str, object for_obj)
{
    return shadow_who->long(str, for_obj)
      + capitalize(LANG_ADDART(POWER_DESC[Power_Level])) + " feeling of"
      + " security emanates from it.\n";
} /* long */


/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The feeling of security emanating from the "
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
    return "This item has been imbued with magic that causes "
      + POWER_LEVEL_DESC[Power_Level] + " healing!";
} /* query_imbue_info */