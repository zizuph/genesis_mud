/* Dirty rag from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("cloth");
    add_name("junk");
    set_adj("tattered");
    add_adj("shred");
    set_short("tattered cloth");
    set_long("This is a tattered old rag. It might have been white before, " + 
        "but there's no way to tell now.\n"); 
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

