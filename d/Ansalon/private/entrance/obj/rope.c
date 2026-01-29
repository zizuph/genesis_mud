/* Rope for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("rope");
    set_adj("long");
    set_short("long rope");
    set_long("This is a long length of old rope. It has been sitting " + 
        "in a damp room for several years, so it doesn't look as sturdy " + 
        "as it used to be.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 120);
}

