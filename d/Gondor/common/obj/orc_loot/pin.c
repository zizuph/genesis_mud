/* A jewelry found on the random orc. */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_object()
{
    set_name("pin");
    add_name(({ "jewelry", "hairpin" }));
    set_adj("silver");
    set_short("silver hairpin");
    set_long(BSN(
    "A large hairpin, made of silver. By the look of the good workmanship, "+
    "it might even have been made by a dwarf."));    
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 125 + random(75));
}
