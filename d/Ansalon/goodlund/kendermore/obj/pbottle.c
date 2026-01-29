/* Purple bottle for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("bottle");
    set_adj("purple");
    set_short("purple bottle");
    set_long("This used to be a normal glass bottle, but years of exposure " + 
        "to the sun has turned it pale purple. It is scratched and " + 
        "chipped, but still intact. The cork is still stuck in the top, " + 
        "but refuses to budge.\n");
    add_prop(OBJ_I_VALUE, 70);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 120);
}

