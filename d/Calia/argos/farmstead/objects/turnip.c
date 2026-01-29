/* /d/Calia/argos/farmstead/objects/turnip.c
**   A turnip, can be either eaten or used in the farmstead quest
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/22/20    Brine      Created
**
*/

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_food()
{
    seteuid(getuid());

    set_name("turnip");

    set_long(
        "A turnip. It looks edible, but it is probably better served cooked.\n"
    );

    set_amount(25); // Stuffed amount

    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 5);
}
