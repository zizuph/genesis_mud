/* Non autoloading tanzanite from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("tanzanite");
    add_name("gem");
    add_name("stone");
    set_adj("violet");
    set_short("violet tanzanite");
    set_long("This stone, also known as Zoisite, is a bright shade somewhere " +
             "between blue and lavender.  It is as beautiful as a fine " +
             "sapphire, and perhaps more limpid.\n");
    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);
}

