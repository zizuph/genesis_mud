/*
 * Shadow for the Mermaid Ring   
 *
 * The Mermaid Ring is a Quest Object that grants the ability
 * to breathe under water. When it is worn, the user should
 * gain the MAGIC_I_BREATH_WATER of a value of 70.
 *
 * Converted to use a shadow in December 2015 because of reports
 * that the ring was not working and occasionally causing people
 * to drown.
 *
 * Created by Petros, December 2015
 */

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"
#include SEA_QUESTS

inherit "/std/shadow";

/*
 * Function:    has_mermaid_ring_shadow
 * Description: Returns whether the user has this shadow or not.
 */
public int
has_mermaid_ring_shadow()
{
    return 1;
}

/*
 * Function:    remove_mermaid_ring_shadow
 * Description: Remove this particular shadow. Need a special function
 *              because calling remove_shadow() will always remove the
 *              top shadow.
 */
public void
remove_mermaid_ring_shadow()
{
    remove_shadow();
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    mixed base_value = shadow_who->query_prop(prop);
    if (prop != MAGIC_I_BREATH_WATER)
    {
        return base_value;
    }

    // We are trying to check the MAGIC_I_BREATH_WATER
    // This shadow only has effect if the player is in a room in the Calia
    // domain.
    object player_room = environment(shadow_who);
    if (!objectp(player_room)
        || !IS_ROOM_OBJECT(player_room)
        || !wildmatch("*Calia*", file_name(player_room)))
    {
        return base_value;
    }

    // Need to also check if the mermaid ring is actually worn or not. If not
    // worn by the player, this ring will also have no effect.
    object mermaid_ring = present(MERMQ_RING_ID, shadow_who);
    if (!objectp(mermaid_ring)
        || !objectp(mermaid_ring->query_worn())
        || mermaid_ring->query_worn() != shadow_who)
    {
        return base_value;
    }
    
    // Now give the higher value of the 70 or what other breathing they
    // may actually already have.
    if (intp(base_value))
    {
        return max(base_value, 70);
    }

    // By default, return 70 as the value. We should only get here
    // if the base value is not an integer
    return 70;
}
