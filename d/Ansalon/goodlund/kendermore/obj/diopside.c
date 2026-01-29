/* Non-autoloading diopside for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("diopside");
    add_name("gem");
    add_name("stone");
    set_adj("green");
    set_short("green diopside");
    set_long("The emeralds you have seen have mostly been a pale green, " +
              "somewhere between leaf green and light blue-green.  A very " +
              "few have been a deep, pure green, but those were small and " +
              "extremely expensive.  This stone is of that colour, even if " +
              "not having quite the same luster.\n");
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

