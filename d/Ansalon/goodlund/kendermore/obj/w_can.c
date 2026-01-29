/* Watering can for flowers in Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("can");
    set_adj("battered");
    add_adj("watering");
    set_short("battered watering can");
    set_long("This old watering can has a few holes in it, but it does " + 
        "its job.\n"); 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 130);
}

