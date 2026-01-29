/*   torch.c : For the random orc */

inherit "/std/torch";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_torch()
{
    set_adj("wooden");
    set_short("wooden torch");
    set_long("The torch is made of tar-drenched wood.\n");
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 45);
}
