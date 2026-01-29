/* Rainbow string for Rat Quest, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name(({"string","_ansalon_r_string_"}));
    set_adj("rainbow");
    add_adj("coloured");
    set_short("rainbow coloured string");
    set_long("There are all colours of the rainbow represented in this " + 
        "small bit of string. It looks great for a collection!\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

