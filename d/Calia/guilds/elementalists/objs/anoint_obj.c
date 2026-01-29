
/*  A player with this invisible object has been anointed with oil in the
 *  chapel for a ceremony
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

create_object()
{
    set_name("_anointed_object");
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VALUE,0);
    set_no_show(1); /* invisible to player */
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
}
