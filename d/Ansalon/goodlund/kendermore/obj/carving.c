/* Carving from Kendermore, Gwyneth, May 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("carving");
    set_adj("wooden");
    set_short("wooden carving");
    set_long("This looks like a clumsy attempt at a first carving. It " + 
      "might be a woman.\n");
    add_prop(OBJ_I_VALUE, 30);
}

