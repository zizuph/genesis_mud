/* Coloured string from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

string *colour=({"red", "orange", "yellow", "green", "blue", "purple"});

void
create_object()
{
    set_name("string");
    set_adj(colour[random(6)]);
    set_long("It's a short piece of coloured string.\n");
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}

