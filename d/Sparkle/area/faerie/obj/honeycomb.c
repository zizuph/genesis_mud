/*
 * A piece of honeycomb
 * -- Finwe, December 2005
 * Updated by Gronkas July 29, 2016 - fixed some typos
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "defs.h"

inherit "/std/object";


void create_object()
{
    set_name(({"honeycomb", "comb"}));
    set_adj("large");
    set_adj("piece");
    set_adj("golden");
    set_short("large piece of golden honeycomb");
    set_pshort("large pieces of golden honeycomb");
    set_long("This is a large piece of golden honeycomb. It was cut from " +
        "a hive and is irregularly shaped. The honeycomb is full of hexagonally " +
        "shaped cells. Many of them are capped over and full of honey.\n");
    add_item(({"cells", "hexagonal cells", "hexagonally shaped cells"}),
        "They are small and have six sides. The cells are stacked on top " +
        "of each other, and are capped and full of honey.\n");
    add_item(({"honey"}),
        "It is golden colored and sealed in cells on the honeycomb.\n");

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VALUE, random(140));

}
