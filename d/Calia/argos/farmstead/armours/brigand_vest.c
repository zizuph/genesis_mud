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

    set_name(({ "vest", "armour" }));
    set_adj(({ "hard", "leather" }));

    set_short("hard leather vest");
    set_long("It is a vest made from hard, rigid leather plates.\n");

    set_ac(8);
    set_am(({ -2, 1, 1 }));

    set_at(A_BODY);

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1500);
}
