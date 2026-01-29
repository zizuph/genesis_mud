/* /d/Calia/argos/farmstead/objects/straw.c
**   A lump of straw, a quest object for the farmstead quest
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

    set_name(({ "straw", "lump", "lump of straw" }));
    set_pname(({ "lumps of straw" }));

    set_short("lump of straw");
    set_pshort("lumps of straw");

    set_long(
        "This is a good handful of wheat straws that have had the grains "
        + "removed. Having grown in nutritious soil and with plenty of sun"
        + "light, they are very healthy looking and are of a beautifully "
        + "golden blonde colour.\n"
    );

    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_M_NO_SELL, "This " + short() + " isn't worth anything.\n");
}
