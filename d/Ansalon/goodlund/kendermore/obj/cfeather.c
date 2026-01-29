/* Coloured feather for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

/* Randomizes the feather colour */

string *colour=({"red", "orange", "yellow", "green", "blue", "purple"});

void
create_object()
{
    set_name("feather");
    add_name("junk");
    set_adj(colour[random(6)]);
    set_long("It's a beautifully coloured feather from some exotic bird.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 15);
}

