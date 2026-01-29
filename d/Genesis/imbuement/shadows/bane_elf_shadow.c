/*
 *  /d/Genesis/imbuement/shadows/bane_elf_shadow.c
 *
 *  This is one of the magic mods that can be applied to weapons or
 *  armours randomly by the imbuement generator:
 *
 *      /d/Genesis/imbuement/imbuement_generator.c
 *
 *  This particular effect gives a special attack when used against elves.
 *
 *  Created September 2010, by Gorboth (Cooper Sherry)
 *    - Special thanks to Lavellan for setting up the bane shadow and
 *      creating an easy-to-follow example!
 *
 *  Added 'dark elf' race to shadow.
 *    - Arman, January 2021
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "bane_base";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public string            stat_object();
public string *          query_races();
public void              init_imbue_shadow(int lvl);
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

    str += "This item has been given a random magic mod that does"
         + " extra death damage (" + POWER_LEVEL_DESC[Power_Level]
         + " amount) roughly 10% of the time to elves.\n";
    return str;
} /* stat_object */


/*
 * Function name: query_races
 * Description:   Returns the races this bane should affect
 * Returns:       str * - Array of race names
 */
public string *
query_races()
{
    return ({ "elf", "drow", "shadow elf", "shadow-elf", 
        "dark elf", "dark-elf", "half-elf" });
} /* query_races */


/*
 * Function name:        init_imbue_shadow
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

    //set_races( ({ "elf", "drow", "shadow elf", "shadow-elf" }) );
    set_hit_descs( ({ "tingles the flesh of", "singes the flesh of",
                      "broils the flesh of", "immolates the flesh of",
                      "destroys the flesh of" }) );
    set_damage_msg("A flash of power erupts from the beryl formations on");
    set_add_item_array(   ({ "glow",
                             "slight glow",
                             "pronounced glow",
                             "intense glow",
                             "beryl",
                             "beryl formation",
                             "beryl formations",
                             "beryls",
                             "formation",
                             "formations",
                             "unusual formation",
                             "unusual beryl formation",
                             "unusual beryl formations",
                             "unusual formations" }) );
    set_add_item_desc(
        "The " + shadow_who->short() + " is covered with unusual beryl"
      + " formations. They look almost organic in the way they are"
      + " clustered, as if some force of nature were responsible for"
      + " their arrangement. It certainly does not look to be part of the"
      + " design of any artisan's craft.\n");
    set_nullstone_type("char");
} /* init_imbue_shadow */

/*
 * Function:    query_formation_type
 * Description: Each bane imbuement shadow has a type of formation that emits
 *              a particular flow. Each one should override this one and
 *              specify a type of formation that forms along the surface.
 */
public string
query_formation_type()
{
    return "beryl";
}

/*
 * Function name: dispel_msg_hook
 * Description:   What observers will see when the mod is dispelled.
 * Returns:       string - the message
 */
public string
dispel_msg_hook()
{
    return "The beryl formations along the surface of the "
      + shadow_who->short() + " melt suddenly into smoke, and vanish.\n";
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
    return "This item has been imbued with elemental magic that causes "
      + POWER_LEVEL_DESC[Power_Level] + "-intensity damage to"
      + " elves!";
} /* query_imbue_info */
