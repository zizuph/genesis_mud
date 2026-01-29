/* Brick in Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("brick");
    add_name("junk");
    set_adj("red");
    add_adj("piece");
    set_short("piece of red brick");
    set_long("This looks like it was chipped off of a building brick.\n"); 
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 90);
    add_prop(OBJ_I_VOLUME, 130);
}

