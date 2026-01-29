inherit "/std/shadow";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <language.h>


/*
 * Function name: short
 * Description  : If the armour is broken, we add the adjective broken to
 *                the short description. There is a little caveat it the
 *                short description has not been explicitly set. In that
 *                case, the adjective broken may appear twice.
 * Arguments    : object for_obj - the object that wants to know.
 * Returns      : string - the short description.
 */
public varargs string
short(object for_obj)
{
    string current_desc = query_shadow_who()->short();

    return "blackened " + current_desc + "";
}

