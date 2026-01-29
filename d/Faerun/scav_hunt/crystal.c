/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    seteuid(getuid());
    set_name("crystal");
    add_name("exquisite cut crystal");
    set_adj("exquisitely cut");
    set_long("This is an exquistely cut crystal. It is tear drop " +
        "shaped and sparkles in the light. A white flame burns " +
        "bright in its center.\n");
    add_prop(OBJ_I_VALUE, 150);

    add_item(({"white flame", "flame"}),
        "The white flame burns brightly. It looks to be ethereal " +
        "as it never goes out, and yet the gem is cool to the touch.\n");
}
