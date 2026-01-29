/*
 * Boots for Faerie Leather Shop
 * Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>

inherit FOOTWEAR_BASE;

void
create_shoes()
{
    setuid(); seteuid(getuid());

    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_name("boots");
    set_pname("boots");
    set_adj("high");
    set_adj("leather");
    set_long("These are a " + short() + ". They are made of leather and " +
        "designed for travel through all kinds of terrain. They come up " +
        "over the calf and are more decorative than protective.\n");
    set_at(A_FEET);
}

void
leave_env(object from, object to)
{
    ::leave_env();
}

