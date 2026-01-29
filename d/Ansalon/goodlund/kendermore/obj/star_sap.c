/* Non autoloading star sapphire for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("sapphire");
    add_name("gem");
    add_name("stone");
    set_adj("blue");
    add_adj("star");
    set_short("blue star sapphire");
    set_long("This stone is an opaque medium blue, but when you rotate " +
             "it in the light you notice a bright six-pointed star " +
             "shining from within.\n");
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

