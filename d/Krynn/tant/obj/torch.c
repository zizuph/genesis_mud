/* A torch coded by Nick */

inherit  "/std/torch";
#include <macros.h>
#include "../local.h"

void
create_torch()
{
    set_name("torch");
    set_pname("torches");          /* The plural name. */
    set_adj("small");
    set_long("A small torch which could make a fine light source.\n");
    set_strength(2);
    set_short("small torch");
    set_pshort("small torches");
}

