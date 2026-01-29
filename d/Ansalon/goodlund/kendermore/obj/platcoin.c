/* Platinum wishing coin from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("coin");
    set_pname("coins");
    set_adj("platinum");
    set_short("platinum coin");
    set_pshort("platinum coins");
    set_long("This is a platinum wishing coin!\n");

    add_prop(OBJ_I_VALUE, 1728);
    add_prop(OBJ_I_WEIGHT, 21);
    add_prop(OBJ_I_VOLUME, 1);
}


