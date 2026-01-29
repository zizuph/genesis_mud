/*
 *  /d/Genesis/guilds/merc/obj/rack_shadow.c
 *
 *  This shadow is added to items entering the mercenary racks. It will add
 *  the special armoury property, and shows the mark of the mercenary armoury
 *  when examined.
 * 
 *  Created by Eowul, 20-9-2003
 */

#include <macros.h>
#include <stdproperties.h>
#include "../merc.h"

#define MERC_ARMOURY "_merc_guild_armoury"

inherit "/std/shadow";

/*
 * Function names: long
 * Description   : The long description. We add the condition information
 *                 to it. This function only returns the string, it does
 *                 not print it to the looker.
 * Arguments     : string str - a possible add-item to look for.
 *                 object for_obj - the object that wants to know.
 * Returns       : string - the long description.
 */
public varargs string long(string str, object for_obj)
{
    string result;

    // Get the original long description
    result = query_shadow_who()->long(str, for_obj);

    // Check if we have a string
    if(!stringp(result))
        return result;

    // Check if we want the long or an add_item
    if(str && strlen(str))
        return result;

    // We want the long description, add the mark
    result +=
        "It bears the mark of the Mercenary Guild Armoury.\n";

    // Return
    return result;
}

/*
 * Function name: query_nosell_property
 * Description  : Special no sell property that does not allow the items
 *                shadowed to be sold in shops, except for non saving
 *                equipment during arma
 * Returns      : a string when not allowed, or 0 if allowed
 */
mixed query_nosell_property()
{
    // If Armageddon is active, allow non saving items to be sold
    if (ARMAGEDDON->shutdown_active() &&
        query_shadow_who()->may_not_recover()) 
        return 0;

    // Either arma is not active, or item recovers
    return "The shopowner does not accept items from the Mercenary racks.\n";
}

/*
 * Function name: shadow_me
 * Description  : Called from object to make us shadow it.
 * Arguments    : mixed to_shadow - either a string or object. If it is
 *                a string, use find_player to find the player to shadow.
 * Returns      : int - True if shadowed.
 */
public varargs int shadow_me(mixed to_shadow)
{
    // Add the armoury property
    to_shadow->add_prop(MERC_ARMOURY, 1);

    // Don't allow the item to be sold
    to_shadow->add_prop(OBJ_M_NO_SELL, query_nosell_property);

    // Do the actual function
    return ::shadow_me(to_shadow);
}


/*
 * Function name: query_recover
 * Description  : Return the recover string
 * Returns      : a string
 */
string query_recover()
{
    string  result;

    // Check the original recover string
    result = query_shadow_who()->query_recover();

    // If we dont recover, just return
    if(!stringp(result))
        return result;

    // Add our own part to the recover string
    result = MOBJ + "rack_recover:" +
        result;

    return result;
}

/*
 * Function name: appraise_object
 * Description  : Appraise this object
 * Arguments    : int num - the semi-randomised appraise skill.
 */
void appraise_object(int num)
{
    // Appraise the object
    query_shadow_who()->appraise_object(num);

    // Write an armoury message
    write("It bears the mark of the Mercenary Guild Armoury.\n");
}

/*
 * Function name: query_mercenary_rack_shadow
 * Description  : See if this object is already shadows by a rack shadow
 * Returns      : always 1
 */
int query_mercenary_rack_shadow()
{
    return 1;
}