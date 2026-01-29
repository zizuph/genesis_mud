/* Gold wishing coin from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("coin");
    set_pname("coins");
    set_adj("gold");
    set_short("gold coin");
    set_pshort("gold coins");
    set_long("This is a gold wishing coin!\n");

    add_prop(OBJ_I_VALUE, 144);
    add_prop(OBJ_I_WEIGHT, 19);
    add_prop(OBJ_I_VOLUME, 1);
}


