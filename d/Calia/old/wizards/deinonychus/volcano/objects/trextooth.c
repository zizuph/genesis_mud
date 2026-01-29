/* File: trextooth.c. A tooth of a tyrannosaurus rex */

inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>

#include "defs.h"

void
create_object()
{
    set_name("tooth");
    set_pname("teeth");
    set_short("t-rex tooth");
    set_pshort("t-rex teeth");
    set_adj("t-rex");
    set_long("It's one of a the deadly teeth of a t-rex. It's quite big and "
        + "sharp.\n");
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 50);
}

