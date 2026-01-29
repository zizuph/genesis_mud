/* Silver wishing coin from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("coin");
    set_pname("coins");
    set_adj("silver");
    set_short("silver coin");
    set_pshort("silver coins");
    set_long("This is a silver wishing coin!\n");

    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_WEIGHT, 21);
    add_prop(OBJ_I_VOLUME, 2);
}


