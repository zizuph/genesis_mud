/* /d/Calia/argos/farmstead/mobiles/brigand_armour.c
**   Armour worn by the brigand leader at the farmstead near Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/3/20    Brine      Created
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

    set_name(({ "armour", "breastplate" }));
    set_adj(({ "studded", "leather" }));

    set_short("studded leather armour");
    set_long(
        "This is a breastplate made by stitching together hardened leather "
        + "sheets that have been tightly riveted with rounded metal studs. "
        + "The inside is lined with thick padding, providing some comfort "
        + "as well as a little added protection for the wearer. It seems "
        + "to be of high quality.\n"
    );

    set_ac(18);
    set_am(({ -2, 1, 1 }));


    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, 6910);
}
