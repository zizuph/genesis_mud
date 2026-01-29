/* Non autoloading tiger eye for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";

void
create_object()
{
    set_name("eye");
    add_name("gem");
    add_name("stone");
    set_adj("tiger's");
    set_short("tiger's eye");
    set_long("This stone is a variety of quartz which has thousands of tiny " +
             "fibers running through it.  It is brown along the sides, but " +
             "has an almost glowing golden streak running down its middle, " +
             "where the fibers reflect rather than catch the light.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

