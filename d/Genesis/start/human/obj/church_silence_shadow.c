inherit "/std/shadow";

#include <stdproperties.h>

/*
 * Function name:   remove_church_silence_shadow
 * Description:     Remove the church silence
 * Arguments:       None
 * Returns:         Nothing
 */
public int
remove_church_silence_shadow()
{
    remove_shadow();
} /* remove_church_silence_shadow */

/*
 * Function name:   query_prop
 * Description:     Find the value of a property. This function is usually
 *                  implemented as CFUN, i.e. as real C implementation in the
 *                  gamedriver as it is used so often. You should NOT mask this
 *                  function in code. Use VBFC on the property value, if you
 *                  must.
 * Arguments:       mixed prop - the name of the property (usually a string).
 * Returns:         mixed - the value of the property, or 0 if the property did
 *                  not exist..
 */
public mixed
query_prop(string prop)
{
    /* Mask the property. */
    if (prop == LIVE_M_MOUTH_BLOCKED)
        return "The local church is a place of tranquility and solitude, and "
        + "you should not break it through idle talk.\n";
        
    return shadow_who->query_prop(prop);
} /* query_prop */