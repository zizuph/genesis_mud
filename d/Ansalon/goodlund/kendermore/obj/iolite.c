/* Non-autoloading gem for Kendermore, and quest item. Gwyneth, June 1999 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name(({"iolite","_ansalon_m_stone_"}));
    add_name("gem");
    add_name("stone");
    set_adj("violet");
    add_adj("blue");
    add_adj("violet-blue");
    set_short("violet-blue iolite");
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    set_keep(1);

    set_long("This is an unusual stone. At first glance, it appears to " + 
        "be violet, but when you turn it slightly, it appears to be clear. " +
        "This particular stone is rumoured to serve as a compass on " + 
        "overcast days, indicating the direction of the sun. It is very " + 
        "valued by travellers for this reason.\n"); 
}

