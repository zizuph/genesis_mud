/* Lockpicks for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("lockpicks");
    set_adj("rusty");
    add_adj("set");
    set_short("set of rusty lockpicks");
    set_pshort("sets of rusty lockpicks");
    set_long("This is a set of rusted and bent lockpicks. They are " + 
        "beyond use.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 120);
}

