/*
 *  /d/Genesis/imbuement/shadows/poison_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect poisons a hit enemy every so often
 *
 *  2010/09/13 Lavellan (descriptions by Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"
#include <macros.h>
#include <files.h>      //for IS_PLAYER_OBJECT

inherit SHADOW_DIR + "imbuement_shadow";

/* Global Variables */
public int               Poison_Alarm;

/* Prototypes */
public string            stat_object();
public void              init_imbue_shadow(int lvl);
public varargs int       did_hit(int aid, string hdesc, int phurt,
                                 object enemy, int dt, int phit, int dam);
public void              recharge();
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

    str += "This weapon has been given a random magic mod that poisons a"
         + " hit enemy every so often.\n";
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

    set_add_item_array(   ({ "drop",
                             "drops",
                             "moisture",
                             "drop of moisture",
                             "drops of moisture",
                             "green moisture",
                             "drop of green moisture",
                             "drops of green moisture",
                             "slightly green moisture",
                             "drop of slightly green moisture",
                             "drops of slightly green moisture",
                             "pronouncedly green moisture",
                             "drop of pronouncedly green moisture",
                             "drops of pronouncedly green moisture",
                             "intensely green moisture",
                             "drop of intensely green moisture",
                             "drops of intensely green moisture", }) );

    set_add_item_desc(
        "The way the drops of green moisture glisten gives you a"
      + " slight thrill. You sense malevolence within this weapon!\n");

    set_nullstone_type("asp");

    setuid();
    seteuid(getuid());
} /* init_imbue_shadow */


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 * 
 * This is masked to apply the poison.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam);
    object pobj;
    object  item_owner = environment(shadow_who);

    if (!objectp(enemy))
    {
        return (rval);
    }

    if (!dam)
    {
        return (rval);
    }

    if (!Poison_Alarm)
    {
        if (present("_imbuement_poison", enemy))
            environment(shadow_who)->catch_vbfc("The poison fails to affect" +
            " the already-poisoned blood of " + QTNAME(enemy) + ".\n");
        else
        {
            set_alarm(0.0, 0.0,&enemy->command("$wail"));
            Poison_Alarm = set_alarm(1200.0, 0.0, recharge);
            pobj = clone_object(SHADOW_DIR + "effect_poison_effect");
            pobj->move(enemy, 1);
            pobj->set_level(Power_Level);
            pobj->start_poison(shadow_who);

        if (IS_PLAYER_OBJECT(item_owner) && IS_PLAYER_OBJECT(enemy))
            IMBUE_LOGGER->log("pvp", sprintf("%s by %s  poison/%s (%d)",
                capitalize(enemy->query_real_name()),
                capitalize(item_owner->query_real_name()),
                shadow_who->short(),
                query_id()));

        }
    }

    return (rval);
} /* did_hit */


/*
 * Function name: recharge
 * Description:   Poison has recharged and is ready for another hit
 */
void
recharge()
{
    if (Poison_Alarm)
        remove_alarm(Poison_Alarm);
    Poison_Alarm = 0;
    string t = "The drops of green moisture clinging to the "
      + shadow_who->short() + " glow brightly.\n";
    if (shadow_who)
        environment(shadow_who)->catch_tell(t);
} /* recharge */

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
    return "Drops of " + POWER_DESC[Power_Level] + "ly green moisture cling to"
      + " this weapon." + 
      (Poison_Alarm ? " The moisture looks a bit dull right now." : "");
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The drops of green moisture clinging to the "
      + shadow_who->short() + " evaporate into nothing.\n";
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
    return "This item has been imbued with the ability to inflict those it"
        + " strikes with a " + POWER_LEVEL_DESC[Power_Level] + "-grade poison!";
} /* query_imbue_info */
