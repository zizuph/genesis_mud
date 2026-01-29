/* Doll from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("doll");
    add_name("junk");
    set_adj("raggedy");
    set_short("raggedy doll");
    set_long("This is a well-loved doll by the looks of it. It has brown " + 
        "yarn hair, a blue-checked dress, and tiny black shoes. One beady " + 
        "eye is missing, and half the hair has been pulled or worn out.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
}

