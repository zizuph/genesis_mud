/* Non-autoloading agate found in Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";

void
create_object()
{
    set_name("agate");
    add_name("gem");
    add_name("junk");
    set_adj("banded");
    set_short("banded agate");
    set_long("This light coloured stone has stripes running across it, of " +
             "various widths and shades, some of them are almost totally " +
             "transparent, others are completely opaque.  You feel like you " +
             "could never find another one exactly the same as this one.\n");
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

