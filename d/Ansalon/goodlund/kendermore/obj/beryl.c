/* Non autoloading beryl for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("beryl");
    add_name("gem");
    add_name("stone");
    add_name("junk");
    set_adj("golden");
    set_short("golden beryl");
    set_long("This stone is a beautiful golden colour -- it doesn't have the " +
             "cold, hard look of an imperial topaz, and you wonder why you " +
             "haven't seen more of this shimmering stone in jewelry before.\n");
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

