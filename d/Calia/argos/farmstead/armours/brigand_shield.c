/* /d/Calia/argos/farmstead/mobiles/brigand_vest.c
**   Leather vest worn by the brigands at the farmstead near Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/2/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

void
create_armour()
{
    seteuid(getuid());

    set_name(({ "shield", "armour", "buckler" }));
    set_adj("wooden");

    set_short("wooden buckler");
    set_long(
        "It is a round wooden buckler with a small metal boss at the center.\n"
    );

    set_ac(10);
    set_am(({ 0, 1, -1 }));

    set_at(A_SHIELD);

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1200);
}
