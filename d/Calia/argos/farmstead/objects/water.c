/* /d/Calia/argos/farmstead/objects/water.c
**   Water to fill the bucket for the farmstead quest, it has
**   no other purpose and will not allow itself to be moved
**   into the inventory of a living
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/23/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_drink()
{
    seteuid(getuid());

    set_name("water");
    set_drink_msg("Uergh, that's some foul tasting water!\n");

    set_short("measure of water");
    set_long(
        "This is a measure of water, just about enough to fill a bucket.\n"
    );

    set_soft_amount(5000);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (MASTER_OB(dest) != (OBJ_DIR + "bucket"))
    {
        if (living(dest))
        {
            dest->catch_tell(
                "The water spills out between your fingers and is gone!\n"
            );
            remove_object();
        }
    }
}
