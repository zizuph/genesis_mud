/* Hammer for Maen, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
inherit "/lib/keep";
inherit "/std/weapon";

create_weapon()
{
    set_name("hammer");
    set_adj("heavy");
    add_adj("steel");
    set_short("heavy steel hammer");
    set_long("This is a heavy hammer. It appears to be used in the smithy " +
        "rather than on the battlefield, but it could be used that way too.\n");
    set_default_weapon(10, 15, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 17000);
    add_prop(OBJ_I_VOLUME, 5000);
    set_keep(1);
}

