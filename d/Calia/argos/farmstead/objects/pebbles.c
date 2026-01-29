/* /d/Calia/argos/farmstead/objects/pebbles.c
**   A handful of pebbles
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/23/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_object()
{
    seteuid(getuid());

    set_name(({ "handful of pebbles", "pebbles", "stones" }));
    set_pname("handfuls of pebbles");

    set_adj(({ "tooth-shaped", "tooth-sized", "smooth" }));

    set_short("handful of pebbles");
    set_pshort("handfuls of pebbles");

    set_long(
        "A handful of smooth pebbles that are roughly the size and shape of "
        + "human teeth.\n"
    );

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_M_NO_SELL, "Why would anyone buy a handful of pebbles?!?\n");
}
