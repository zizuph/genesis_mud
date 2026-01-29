/* Copper wishing coin from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("coin");
    set_pname("coins");
    set_adj("copper");
    set_short("copper coin");
    set_pshort("copper coins");
    set_long("This is a copper wishing coin!\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 18);
    add_prop(OBJ_I_VOLUME, 2);
}


