/* White pigeon feather for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("feather");
    set_adj("white");
    set_short("white feather");
    set_long("It looks like it came from a pigeon.\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 20);
}
